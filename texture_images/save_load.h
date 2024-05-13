//
// Created by Torben Bernhard on 4/27/24.
//

#ifndef CG_PROJECT_SAVE_LOAD_H
#define CG_PROJECT_SAVE_LOAD_H



namespace texture_images
{
    class save_load
    {
    public:
        static unsigned char* loadImage(const char* filename, int& width, int& height, int& numChannels);
    };


}

#endif //CG_PROJECT_SAVE_LOAD_H
