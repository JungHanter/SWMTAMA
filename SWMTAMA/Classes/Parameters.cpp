//
//  Parameters.cpp
//  JNI_VoiceRecogTest
//
//  Created by Jung Hanter on 12. 11. 7..
//
//

#include "Parameters.h"

Parameters* Parameters::create(int arg1) {
    Parameters* param = new Parameters(arg1);
    param->autorelease();
    return param;
}

Parameters* Parameters::create(int arg1, int arg2) {
    Parameters* param = new Parameters(arg1, arg2);
    param->autorelease();
    return param;
}

Parameters* Parameters::create(int arg1, int arg2, int arg3) {
    Parameters* param = new Parameters(arg1, arg2, arg3);
    param->autorelease();
    return param;
}

Parameters::Parameters(int arg1) : cocos2d::CCObject() {
    this->arg1 = arg1;
}

Parameters::Parameters(int arg1, int arg2) : cocos2d::CCObject() {
    this->arg1 = arg1;
    this->arg2 = arg2;
}

Parameters::Parameters(int arg1, int arg2, int arg3) : cocos2d::CCObject() {
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->arg3 = arg3;
}