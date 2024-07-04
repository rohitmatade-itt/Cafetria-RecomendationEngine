#ifndef REQUESTTYPE_H
#define REQUESTTYPE_H

enum class RequestType {
    LOGIN_REQUEST = 1,
    DISPLAY_MENU_REQUEST,
    VIEW_SPECIFIC_DATE_MENU_REQUEST,
    ADD_EMPLOYEE_REQUEST,
    REMOVE_EMPLOYEE_REQUEST,
    ADD_MENU_ITEM_REQUEST,
    REMOVE_MENU_ITEM_REQUEST,
    GENERATE_REPORT_REQUEST,
    GET_RECOMMENDATION,
    ROLLOUT_NEXT_DAY_MENU,
    GET_NEXT_DAY_MENU_REQUEST,
    GET_USER_RECOMMENDATION,
    VOTE_NEXT_DAY_MENU,
    GIVE_FEEDBACK,
    VIEW_NEXT_DAY_VOTES,
    GET_USER_VOTE_LIST,
    GET_USER_PROFILE,
    UPDATE_USER_PROFILE
};

#endif // REQUESTTYPE_H
