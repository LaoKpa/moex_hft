//
// Created by root on 18.07.16.
//

#ifndef HFT_ROBOT_LOGERRORMESSAGECODES_H
#define HFT_ROBOT_LOGERRORMESSAGECODES_H

typedef enum _LogMessageCode {
#pragma region LogMessageCodes_GeneratedCode
    lmcNone = 0,
    lmcSuccess = 1,
    lmcFailed = 2
#pragma  endregion
}LogMessageCode;


class LogMessageProvider {
    const char **LogMessageText;

    void InitializeLogMessageText();
public:
    LogMessageProvider();
    ~LogMessageProvider();

};

#endif //HFT_ROBOT_LOGERRORMESSAGECODES_H