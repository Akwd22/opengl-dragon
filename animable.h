#ifndef ANIMABLE_H
#define ANIMABLE_H

class Animable
{
    public:
        Animable();
        void toggleAnimation();
        void playAnimation();
        void stopAnimation();
        void tickAnimation();

    protected:
        bool isAnimating;
};

#endif // ANIMABLE_H
