#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <time.h>
#include "Camera.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Ray.h"
#include "Primitive.h"
#include "Ellipsoid.h"
#include "DirectionalLight.h"
#include "Random.h"
#include "Scene.h"
#include "IntersectionResponse.h"

const int WIDTH = 1280;//640,960,1024,1280,1366,1600,1920,2560,3200,3840,5120,7680
const int HEIGHT = 720;//360,540,576, 720, 760, 900, 1080,1440,1800,2160,2880,4320
unsigned char buffer[WIDTH * HEIGHT * 4]; // BGRA format

void draw(int t);

void draw2();

void draw3();

static void write_colour(ColourRGB pixel_colour, int x, int y);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI main(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    ////BOILER PLATE
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"RawWindowClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, L"RawWindowClass", L"Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    //Call to actually draw to the buffer

    HDC hdc = GetDC(hwnd);
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = WIDTH;
    bmi.bmiHeader.biHeight = -HEIGHT; // Top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    draw2();

    MSG msg = { };
    int i = 0;
    while (true) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) return 0;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //draw2();

        //std::cout << "iteration: " << i << std::endl;
        //i++;

        StretchDIBits(hdc, 0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT,
            buffer, &bmi, DIB_RGB_COLORS, SRCCOPY);
    }

    return 0;
}

ColourRGB RayToColour(const Ray& a_ray)
{
    //The Direction Variable is a vector which is normalized
    //This means its x y and z values range -1 to 1
    //To convert these into ranging from 0 to 1 we have to add 1 and times by a half
    return (a_ray.Direction() + 1.f) * 0.5f;
}

static void write_colour(ColourRGB pixel_colour, int x, int y)
{
    // find the index in the buffer array for the pixel at (x, y)
    // Each pixel occupies 4 consecutive integers: Blue, Green, Red, and Alpha
    // For example, for pixels in the top row, y is 0
    // Therefore moving from pixel 1 to pixel 2 is simply multiplying by 4 to get the next quadruple of integers
    // And when y increments by 1 we move along the buffer as many pixels as a row is long so that x once again starts at leftmost pixel
    int i = (y * WIDTH + x) * 4;
    //index each of the channels and set the value to between 0 and 255.999
    //pixel_colour.x y and z are all between 0 and 1
    buffer[i + 0] = int(255.999 * pixel_colour.z); // Blue
    buffer[i + 1] = int(255.999 * pixel_colour.y); // Green
    buffer[i + 2] = int(255.999 * pixel_colour.x); // Red
    buffer[i + 3] = 0;     // Alpha
}

Vector3 Cross(const Vector3& a_v3A, const Vector3& a_v3B)
{
    return Vector3(
        a_v3A.y * a_v3B.z - a_v3A.z * a_v3B.y,
        a_v3A.z * a_v3B.x - a_v3A.x * a_v3B.z,
        a_v3A.x * a_v3B.y - a_v3A.y * a_v3B.x
    );
}

void draw(int t)
{
    float aspectRatio = (float)WIDTH / (float)HEIGHT;

    float nearPlaneHeight = 2.f;
    float nearPlaneWidth = aspectRatio * nearPlaneHeight;
    float nearPlaneDistance = 1.f;

    Vector3 cameraPosition = Vector3(0.f, 0.f, 10.f);

    Vector3 cameraRight = Vector3(1.f, 0.f, 0.f);
    Vector3 cameraUp = Vector3(0.f, 1.f, 0.f);
    Vector3 cameraFwd = Vector3(0.f, 0.f, 1.f);

    float waveAmplitude = 1.0f;     // height of the wave
    float waveFrequency = 0.1f;    // speed of the wave
    Vector3 spherePos = Vector3(std::cos(t * waveFrequency) * waveAmplitude, std::sin(t * waveFrequency) * waveAmplitude, -1.f);//move ball in circle
    float sphereRadius = 0.5f;

    cameraFwd = Vector3(0.f, 0.f, -1.f) - cameraPosition;
    cameraFwd.Normalize();
    cameraRight = Cross(Vector3(0.f, 1.f, 0.f), cameraFwd);
    cameraRight.Normalize();
    cameraUp = Cross(cameraFwd, cameraRight);

    float imageWidthToPlaneRatio = nearPlaneWidth / (float)WIDTH;
    float imageHeightToPlaneRatio = nearPlaneHeight / (float)HEIGHT;

    Vector3 upperLeftCorner = cameraPosition + cameraFwd * nearPlaneDistance - cameraRight * (nearPlaneWidth * 0.5f) + cameraUp * (nearPlaneHeight * 0.5f);

    for (int y = 0; y < HEIGHT; ++y)
    {
        float vPos = (float)y * imageHeightToPlaneRatio;

        for (int x = 0; x < WIDTH; ++x)
        {
            float hPos = (float)x * imageWidthToPlaneRatio;

            Vector3 offset = cameraRight * hPos + cameraUp * -vPos + cameraFwd * 0.f;
            Ray viewRay(cameraPosition, (upperLeftCorner + offset) - cameraPosition);

            //std::cout << viewRay.Direction().z << std::endl;

            ColourRGB rayColour;
            float intersectDistance = viewRay.IntersectSphere(spherePos, sphereRadius);
            if (intersectDistance > 0.f)
            {
                Vector3 surfaceNormal = viewRay.PointAt(intersectDistance) - spherePos;
                surfaceNormal.Normalize();
                //surfaceNormal = Vector3(surfaceNormal.x, surfaceNormal.y, -surfaceNormal.z);
                rayColour = (surfaceNormal + 1.f) * 0.5f;
            }
            else
            {
                rayColour = RayToColour(viewRay);
                rayColour = Lerp(Vector3(1.f, 1.f, 1.f), Vector3(0.4f, 0.7f, 1.f), rayColour.y);
            }

            write_colour(rayColour, x, y);
        }
    }
}

void draw2()
{
    Scene mainScene;

    Camera mainCamera;
    mainCamera.SetPerspective(60.f, (float)WIDTH / (float)HEIGHT, 1.f, 1000.f);
    mainCamera.SetPosition(Vector3(0.f, 0.f, 0.f));
    mainCamera.LookAt(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));

    DirectionalLight dl = DirectionalLight(Matrix4(), Vector3(0.5f, 0.f, 0.5f), Vector3(0.5773f, -0.5773f, -0.707f));

    Ellipsoid s1(Vector3(0.f, 0.f, -3.f), 0.5f);
    s1.m_colour = Vector3(0.5f, 0.f, 0.5f);
    Ellipsoid s2(Vector3(0.f, -100.5f, -3.f), 100.f);
    s2.m_colour = Vector3(0.f, 0.5f, 0.f);
    Ellipsoid s3(Vector3(3.f, 0.f, -3.f), 0.5f);
    s3.m_colour = Vector3(0.f, 0.f, 0.5f);
    Ellipsoid s4(Vector3(-3.f, 0.f, -3.f), 0.5f);
    s4.m_colour = Vector3(0.f, 0.f, 0.5f);

    mainScene.AddObject(&s1);
    mainScene.AddObject(&s2);
    mainScene.AddObject(&s3);
    mainScene.AddObject(&s4);

    float invWidth = 1.f / (float)WIDTH;
    float invHeight = 1.f / (float)HEIGHT;

    for (int y = 0; y < HEIGHT; ++y)
    {
        float screenSpaceY = 1.f - 2.f * ((float)y + 0.5f) * invHeight;
        std::cout << "Rendering screenline: " << y << std::endl;
        for (int x = 0; x < WIDTH; ++x)
        {
            ColourRGB rayColour(0.f, 0.f, 0.f);
            float screenSpaceY = 1.f - 2.f * ((float)y + Random::RandFloat()) * invHeight;
            float screenSpaceX = 2.f * ((float)x + Random::RandFloat()) * invWidth - 1.f;

            Vector2 screenSpacePos = Vector2(screenSpaceX, screenSpaceY);
            Ray viewRay = mainCamera.CastRay(screenSpacePos);

            Vector3 hitPos = Vector3(0.f, 0.f, 0.f);
            Vector3 surfNormal = Vector3(0.f, 0.f, 0.f);

            IntersectResponse ir;

            if (mainScene.IntersectTest(viewRay, ir))
            {
                rayColour = dl.CalculateLighting(ir, mainCamera.GetPosition());
            }
            else
            {
                Vector3 rayToColour = RayToColour(viewRay);
                rayColour = rayColour + Lerp(Vector3(1.f, 1.f, 1.f), Vector3(0.4f, 0.7f, 1.f), rayToColour.y);
            }
            write_colour(rayColour, x, y);
        }
    }
}
void draw3()
{
    Scene mainScene;

    Camera mainCamera;
    mainCamera.SetPerspective(60.f, (float)WIDTH / (float)HEIGHT, 1.f, 1000.f);
    mainCamera.SetPosition(Vector3(0.f, 0.f, 0.f));
    mainCamera.LookAt(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));

    DirectionalLight dl = DirectionalLight(Matrix4(), Vector3(0.5f, 0.f, 0.5f), Vector3(0.5773f, -0.5773f, -0.707f));

    Ellipsoid s1(Vector3(0.f, 0.f, -3.f), 0.5f);
    s1.m_colour = Vector3(0.5f, 0.f, 0.5f);
    Ellipsoid s2(Vector3(0.f, -100.5f, -3.f), 100.f);
    s2.m_colour = Vector3(0.f, 0.5f, 0.f);
    Ellipsoid s3(Vector3(3.f, 0.f, -3.f), 0.5f);
    s3.m_colour = Vector3(0.f, 0.f, 0.5f);
    Ellipsoid s4(Vector3(-3.f, 0.f, -3.f), 0.5f);
    s4.m_colour = Vector3(0.f, 0.f, 0.5f);

    mainScene.AddObject(&s1);
    mainScene.AddObject(&s2);
    mainScene.AddObject(&s3);
    mainScene.AddObject(&s4);

    float invWidth = 1.f / (float)WIDTH;
    float invHeight = 1.f / (float)HEIGHT;

    Random::SetSeed(time(nullptr));
    int raysPerPixel = 50;

    for (int y = 0; y < HEIGHT; ++y)
    {
        float screenSpaceY = 1.f - 2.f * ((float)y + 0.5f) * invHeight;
        std::cout << "Rendering screenline: " << y << std::endl;
        for (int x = 0; x < WIDTH; ++x)
        {
            ColourRGB rayColour(0.f, 0.f, 0.f);
            for (int p = 0; p < raysPerPixel; ++p)
            {
                float screenSpaceY = 1.f - 2.f * ((float)y + Random::RandFloat()) * invHeight;
                float screenSpaceX = 2.f * ((float)x + Random::RandFloat()) * invWidth - 1.f;

                Vector2 screenSpacePos = Vector2(screenSpaceX, screenSpaceY);
                Ray viewRay = mainCamera.CastRay(screenSpacePos);

                Vector3 hitPos = Vector3(0.f, 0.f, 0.f);
                Vector3 surfNormal = Vector3(0.f, 0.f, 0.f);

                IntersectResponse ir;

                if (mainScene.IntersectTest(viewRay, ir))
                {
                    rayColour = rayColour + dl.CalculateLighting(ir, mainCamera.GetPosition());
                }
                else
                {
                    Vector3 rayToColour = RayToColour(viewRay);
                    rayColour = rayColour + Lerp(Vector3(1.f, 1.f, 1.f), Vector3(0.4f, 0.7f, 1.f), rayToColour.y);
                }
            }
            rayColour = rayColour * (1.f / (float)raysPerPixel);
            write_colour(rayColour, x, y);
        }
    }
}