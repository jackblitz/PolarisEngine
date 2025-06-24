//
// Created by luke on 6/23/2025.
//

#ifndef PLATFORMRENDERING_H
#define PLATFORMRENDERING_H

class PlatformRendering {
    public:
    PlatformRendering();
    ~PlatformRendering();

    static PlatformRendering* getInstance();

protected:
    static PlatformRendering* instance;
};

#endif //PLATFORMRENDERING_H
