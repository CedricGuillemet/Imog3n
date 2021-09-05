#pragma once

namespace Imog3n {

    struct Input
    {
        int mX, mY;
        int mDeltaX, mDeltaY;
        bool mButtonsDown[3]{ false, false, false };
        bool mControlDown{false};
        float mWheel{};
    };

} // namespace