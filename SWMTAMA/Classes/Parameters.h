//
//  Parameters.h
//  JNI_VoiceRecogTest
//
//  Created by Jung Hanter on 12. 11. 7..
//
//

#ifndef __JNI_VoiceRecogTest__Parameters__
#define __JNI_VoiceRecogTest__Parameters__

#include "cocos2d.h"

class Parameters : public cocos2d::CCObject {
public:
    int arg1, arg2, arg3;
    
    static Parameters* create(int arg1);
    static Parameters* create(int arg1, int arg2);
    static Parameters* create(int arg1, int arg2, int arg3);
    
private:
    Parameters(int arg1);
    Parameters(int arg1, int arg2);
    Parameters(int arg1, int arg2, int arg3);
};

#endif /* defined(__JNI_VoiceRecogTest__Parameters__) */
