//
// Created by luke on 6/23/2025.
//

#ifndef PLATFORMRENDERING_H
#define PLATFORMRENDERING_H

class PlatformRenderer {
    public:
    PlatformRenderer();
    ~PlatformRenderer();

    static PlatformRenderer* getInstance();

protected:
    static PlatformRenderer* _instance;
};

#endif //PLATFORMRENDERING_H
