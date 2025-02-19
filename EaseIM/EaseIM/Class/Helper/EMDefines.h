//
//  EMDefines.h
//  ChatDemo-UI3.0
//
//  Created by XieYajie on 2019/2/11.
//  Copyright © 2019 XieYajie. All rights reserved.
//

#ifndef EMDefines_h
#define EMDefines_h

#define kIsBangsScreen ({\
    BOOL isBangsScreen = NO; \
    if (@available(iOS 11.0, *)) { \
    UIWindow *window = [[UIApplication sharedApplication].windows firstObject]; \
    isBangsScreen = window.safeAreaInsets.bottom > 0; \
    } \
    isBangsScreen; \
})

#define EMVIEWTOPMARGIN (kIsBangsScreen ? 34.f : 0.f)

//weak & strong self
#define EM_WS                  __weak __typeof(&*self)weakSelf = self;
#define EM_SS(WKSELF)          __strong __typeof(&*self)strongSelf = WKSELF;


//appkey
//#define DEF_APPKEY @"41351358#427351"
//#define DEF_APPKEY @"easemob-demo#testmd1"
#define DEF_APPKEY @"easemob-demo#easeim"
//#define DEF_APPKEY @"easemob-demo#chatdemoui"

// 翻译
#define TRANSLATE_KEY @""
#define TRANSLATE_ENDPOINT @""
#define TRANSLATE_LOCATION @""


#define RTC_BUTTON_WIDTH 65
#define RTC_BUTTON_HEIGHT 90
#define RTC_BUTTON_PADDING ([UIScreen mainScreen].bounds.size.width - RTC_BUTTON_WIDTH * 3) / 4

#define EMSYSTEMNOTIFICATIONID @"emsystemnotificationid"

//会话
#define CONVERSATION_STICK @"stick"
#define CONVERSATION_ID @"conversationId"
#define CONVERSATION_OBJECT @"conversationObject"

//账号状态
#define ACCOUNT_LOGIN_CHANGED @"loginStateChange"
#define NOTIF_NAVICONTROLLER @"EMNaviController"
#define NOTIF_ID @"EMNotifId"

//聊天
#define CHAT_PUSHVIEWCONTROLLER @"EMPushChatViewController"
#define CHAT_CLEANMESSAGES @"EMChatCleanMessages"
#define CHAT_BACKOFF @"EMChatBackOff"

//通话
#define EMCOMMMUNICATE_RECORD @"EMCommunicateRecord" //本地通话记录
#define EMCOMMMUNICATE @"EMCommunicate" //远端通话记录
#define EMCOMMUNICATE_TYPE @"EMCommunicateType"
#define EMCOMMUNICATE_TYPE_VOICE @"EMCommunicateTypeVoice"
#define EMCOMMUNICATE_TYPE_VIDEO @"EMCommunicateTypeVideo"
#define EMCOMMUNICATE_DURATION_TIME @"EMCommunicateDurationTime"

//通话状态
#define EMCOMMUNICATE_MISSED_CALL @"EMCommunicateMissedCall" //（通话取消）
#define EMCOMMUNICATE_CALLER_MISSEDCALL @"EMCommunicateCallerMissedCall" //（我方取消通话）
#define EMCOMMUNICATE_CALLED_MISSEDCALL @"EMCommunicateCalledMissedCall" //（对方拒绝接通）
//发起邀请
#define EMCOMMUNICATE_CALLINVITE @"EMCommunicateCallInvite" //（发起通话邀请）
//通话发起方
#define EMCOMMUNICATE_DIRECTION @"EMCommunicateDirection"
#define EMCOMMUNICATE_DIRECTION_CALLEDPARTY @"EMCommunicateDirectionCalledParty"
#define EMCOMMUNICATE_DIRECTION_CALLINGPARTY @"EMCommunicateDirectionCallingParty"

//消息动图
#define MSG_EXT_GIF_ID @"em_expression_id"
#define MSG_EXT_GIF @"em_is_big_expression"

#define MSG_EXT_READ_RECEIPT @"em_read_receipt"

//消息撤回
#define MSG_EXT_RECALL @"em_recall"

//新通知
#define MSG_EXT_NEWNOTI @"em_noti"

//加群/好友 成功
#define NOTIF_ADD_SOCIAL_CONTACT @"EMAddSocialContact"

//加群/好友 类型
#define NOTI_EXT_ADDFRIEND @"add_friend"
#define NOTI_EXT_ADDGROUP @"add_group"

//多人会议邀请
#define MSG_EXT_CALLOP @"em_conference_op"
#define MSG_EXT_CALLID @"em_conference_id"
#define MSG_EXT_CALLPSWD @"em_conference_password"

//@
//群组消息ext的字段，用于存放被@的环信id数组
#define MSG_EXT_AT @"em_at_list"
//群组消息ext字典中，kGroupMessageAtList字段的值，用于@所有人
#define MSG_EXT_ATALL @"all"

//Typing
#define MSG_TYPING_BEGIN @"TypingBegin"
#define MSG_TYPING_END @"TypingEnd"

#define kHaveUnreadAtMessage    @"kHaveAtMessage"
#define kAtYouMessage           1
#define kAtAllMessage           2

//实时音视频
#define CALL_CHATTER @"chatter"
#define CALL_TYPE @"type"
#define CALL_PUSH_VIEWCONTROLLER @"EMPushCallViewController"
//实时音视频1v1呼叫
#define CALL_MAKE1V1 @"EMMake1v1Call"
//实时音视频多人
#define CALL_MODEL @"EMCallForModel"
#define CALL_MAKECONFERENCE @"EMMakeConference"
#define CALL_SELECTCONFERENCECELL @"EMSelectConferenceCell"
#define CALL_INVITECONFERENCEVIEW @"EMInviteConverfenceView"

//用户黑名单
#define CONTACT_BLACKLIST_UPDATE @"EMContactBlacklistUpdate"
#define CONTACT_BLACKLIST_RELOAD @"EMContactReloadBlacklist"

//群组
#define GROUP_LIST_PUSHVIEWCONTROLLER @"EMPushGroupsViewController"
#define GROUP_INFO_UPDATED @"EMGroupInfoUpdated"
#define GROUP_SUBJECT_UPDATED @"EMGroupSubjectUpdated"
#define GROUP_INFO_REFRESH @"EMGroupInfoRefresh"
#define GROUP_INFO_PUSHVIEWCONTROLLER @"EMPushGroupInfoViewController"
#define GROUP_INFO_CLEARRECORD @"EMGroupInfoClearRecord"
#define GROUP_LIST_FETCHFINISHED @"EMGroupListFetchFinished"

//聊天室
#define CHATROOM_LIST_PUSHVIEWCONTROLLER @"EMPushChatroomsViewController"
#define CHATROOM_INFO_UPDATED @"EMChatroomInfoUpdated"
#define CHATROOM_INFO_PUSHVIEWCONTROLLER @"EMPushChatroomInfoViewController"

//用户属性更新
#define USERINFO_UPDATE @"EMUserInfoUpdated"

//确认发送名片消息
#define CONFIRM_USERCARD @"EMUserCardConfirm"

#endif /* EMDefines_h */
