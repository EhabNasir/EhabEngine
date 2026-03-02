
struct Camera
{
    float xPos = 0.0f;
    float yPos = 0.0f;

    float zoom = 1.0f;

    float GetVisibleWidth(float screenWidth) const
    {
        return screenWidth / zoom;
    }

    float GetVisibleHeight(float screenHeight) const
    {
        return screenHeight / zoom;
    }
};