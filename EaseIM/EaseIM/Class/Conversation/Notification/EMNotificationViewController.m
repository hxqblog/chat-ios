//
//  EMNotificationViewController.m
//  ChatDemo-UI3.0
//
//  Created by XieYajie on 2019/1/10.
//  Copyright © 2019 XieYajie. All rights reserved.
//

#import "EMNotificationViewController.h"

#import "EMNotificationHelper.h"
#import "EMNotificationCell.h"

@interface EMNotificationViewController ()<EMNotificationsDelegate, EMNotificationCellDelegate>

@property (nonatomic, strong) NSMutableArray *dataArray;

@end

@implementation EMNotificationViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    self.dataArray = [[NSMutableArray alloc] init];

    [self _setupViews];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    EMConversation *conversation = [EMClient.sharedClient.chatManager getConversation:EMSYSTEMNOTIFICATIONID type:EMConversationTypeChat createIfNotExist:YES];
    [EaseIMKitManager.shared markAllMessagesAsReadWithConversation:conversation];
    [[EMNotificationHelper shared] markAllAsRead];
    [EMNotificationHelper shared].isCheckUnreadCount = NO;
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [[NSNotificationCenter defaultCenter] postNotificationName:CHAT_BACKOFF object:nil];
    [EMNotificationHelper shared].isCheckUnreadCount = YES;
}

- (void)dealloc
{
    [EMNotificationHelper shared].isCheckUnreadCount = YES;
}

#pragma mark - Subviews

- (void)_setupViews
{
    [self addPopBackLeftItem];
    self.title = NSLocalizedString(@"systemNotice", nil);
    
    self.tableView.backgroundColor = kColor_LightGray;
    self.tableView.estimatedRowHeight = 150;
    self.tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [[EMNotificationHelper shared].notificationList count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    EMNotificationModel *model = [[EMNotificationHelper shared].notificationList objectAtIndex:indexPath.row];
    NSString *cellIdentifier = [NSString stringWithFormat:@"EMNotificationCell_%@", @(model.status)];
    EMNotificationCell *cell = (EMNotificationCell *)[tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    
    // Configure the cell...
    if (cell == nil) {
        cell = [[EMNotificationCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
        cell.delegate = self;
    }
    
    cell.model = model;
    
    return cell;
}

#pragma mark - EMNotificationCellDelegate

- (void)agreeNotification:(EMNotificationModel *)aModel
{
    __weak typeof(self) weakself = self;
    void (^block) (EMError *aError) = ^(EMError *aError) {
        if (!aError) {
            aModel.status = EMNotificationModelStatusAgreed;
            [[EMNotificationHelper shared] archive];
            
            [weakself.tableView reloadData];
        }
    };
    
    if (aModel.type == EMNotificationModelTypeContact) {
        [[EMClient sharedClient].contactManager approveFriendRequestFromUser:aModel.sender completion:^(NSString *aUsername, EMError *aError) {
            if (!aError) {
                NSString *msg = [NSString stringWithFormat:NSLocalizedString(@"acceptPrompt", nil),aModel.sender];
                [self showAlertWithTitle:@"O(∩_∩)O" message:msg];
            }
            block(aError);
        }];
    } else if (aModel.type == EMNotificationModelTypeGroupInvite) {
        [[EMClient sharedClient].groupManager acceptInvitationFromGroup:aModel.groupId inviter:aModel.sender completion:^(EMGroup *aGroup, EMError *aError) {
            block(aError);
            if (!aError) {
                NSString *msg = [NSString stringWithFormat:NSLocalizedString(@"joinGroupPrompt", nil),aGroup.groupName];
                [self showAlertWithTitle:@"O(∩_∩)O" message:msg];
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIF_ADD_SOCIAL_CONTACT object:@{CONVERSATION_ID:aModel.groupId,CONVERSATION_OBJECT:EMClient.sharedClient.currentUsername}];
            }
        }];
    } else if (aModel.type == EMNotificationModelTypeGroupJoin) {
        [[EMClient sharedClient].groupManager approveJoinGroupRequest:aModel.groupId sender:aModel.sender completion:^(EMGroup *aGroup, EMError *aError) {
            block(aError);
        }];
    }
}

- (void)declineNotification:(EMNotificationModel *)aModel
{
    __weak typeof(self) weakself = self;
    void (^block) (EMError *aError) = ^(EMError *aError) {
        if (!aError) {
            aModel.status = EMNotificationModelStatusDeclined;
        } else {
            if (aError.code == EMErrorGroupInvalidId) {
                aModel.status = EMNotificationModelStatusExpired;
            }
        }
        
        [[EMNotificationHelper shared] archive];
        [weakself.tableView reloadData];
    };
    
    if (aModel.type == EMNotificationModelTypeContact) {
        [[EMClient sharedClient].contactManager declineFriendRequestFromUser:aModel.sender completion:^(NSString *aUsername, EMError *aError) {
            if (!aError) {
                NSString *msg = [NSString stringWithFormat:NSLocalizedString(@"refusePrompt", nil),aModel.sender];
                [self showAlertWithTitle:@"O(∩_∩)O" message:msg];
            }
            block(aError);
        }];
    } else if (aModel.type == EMNotificationModelTypeGroupInvite) {
        [[EMClient sharedClient].groupManager declineGroupInvitation:aModel.groupId inviter:aModel.sender reason:nil completion:^(EMError *aError) {
            block(aError);

        }];
    } else if (aModel.type == EMNotificationModelTypeGroupJoin) {
        [[EMClient sharedClient].groupManager declineJoinGroupRequest:aModel.groupId sender:aModel.sender reason:nil completion:^(EMGroup *aGroup, EMError *aError) {
            block(aError);
           
        }];
    }
}

@end
