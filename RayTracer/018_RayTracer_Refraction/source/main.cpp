
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "ColorRGB.h"
#include "Camera.h"
#include <libMath.h>
#include "Ellipsoid.h"
#include "DirectionalLight.h"
#include <time.h>
#include <Random.h>
#include "Scene.h"
#include "Material.h"

typedef enum input_args
{
	OUTPUT_FILE = 1,
	OUTPUT_WIDTH,
	OUTPUT_HEIGHT,
}input_args;

void DisplayUsage(char* a_path)
{
	std::string fullpath = a_path; // Get the full path as a string
		// Strip off the path part of the string to only keep the executable name
	std::string exeName = fullpath.substr(fullpath.find_last_of("\\") + 1, fullpath.length());
	// Display a message to the user indicating the usage of the executable
	std::cout << "usage: " << exeName << " [output image name] [image width] [image height]" << std::endl;
	std::cout << "\t-h or --help\t\tShow this message" << std::endl;
}

int main(int argv, char* argc[])
{
	// Setup dimensions of the image
	int imageWidth = 1920;
	int imageHeight = 1080;
	int channelColours = 255;
	// Output file name
	std::string outputFileName;

	// By default the executable path and name are passed into the variadic arguments
	for (int i = 0; i <= argv - 1; i++)
	{
		std::cout << "Variadic Argument [" << i << "] = " << argc[i] << std::endl;
	}

	if (argv < 2) // Less than 2 as the path and executable name are always present
	{
		DisplayUsage(argc[0]);
		return EXIT_SUCCESS;
	}
	else // Some variadic arguments have been passed
	{
		for (int i = 1; i < argv; i++)
		{
			std::string arg = argc[i];
			if (arg == "-h" || arg == "--help")
			{
				DisplayUsage(argc[0]);
				return EXIT_SUCCESS;
			}
			switch (i)
			{
			case OUTPUT_FILE:
			{
				outputFileName = argc[OUTPUT_FILE];
				// Check to see id the extension was included
				if (outputFileName.find_last_of(".") == std::string::npos)
				{
					// No extension, better add one
					outputFileName.append(".ppm");
				}
				break;
			}

			case OUTPUT_WIDTH:
			{
				imageWidth = atoi(argc[OUTPUT_WIDTH]);
				break;
			}

			case OUTPUT_HEIGHT:
			{
				imageHeight = atoi(argc[OUTPUT_HEIGHT]);
				break;
			}

			default:
			{
				continue;
			}
			}
		}
	}

	// Need to change std::cout to outputFileName
	std::streambuf* backup = std::cout.rdbuf(); // Backup std::cout's stream to buffer
	std::ofstream outbuff(outputFileName.c_str()); // Create an out file stream and set it to our output file name
	std::cout.rdbuf(outbuff.rdbuf()); // Set the stream buffer for cout to the file out stream buffer

	Scene mainScene;

	Camera mainCamera;
	mainCamera.SetPerspective(60.0f, (float)imageWidth / (float)imageHeight, 0.1f, 1000.0f);
	mainCamera.SetPosition(Vector3(0.0f, 0.0f, 1.0f));
	mainCamera.LookAt(Vector3(0.0f, 0.0f, -2.5f), Vector3(0.0f, 1.0f, 0.0f));

	Random::SetSeed(time(nullptr));
	int raysPerPixel = 50;
	
	// Output the image header data
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << channelColours << std::endl;

	// Put a light in the scene
	DirectionalLight d1 = DirectionalLight(Matrix4::IDENTITY, Vector3(0.7f, 0.7f, 0.7f), Vector3(-0.5773f, -0.5773f, -0.5773f));

	// Define some materials for use with any objects in the scene
	Material lightBlueSmooth = Material(Vector3(0.2f, 0.6f, 1.0f),	0.1f, 0.3f, 0.8f, 0.0f, 0.8f, 0.9f, 1.52f);
	Material lightBlueRough = Material(Vector3(0.2f, 0.6f, 1.0f),	0.2f, 0.9f, 0.3f, 0.02f, 0.6f, 0.0f, 1.52f);
	Material greenSmooth = Material(Vector3(0.0f, 0.6f, 0.0f),		0.2f, 0.3f, 0.9f, 0.0f, 0.0f, 1.0f, 1.52f);
	Material greenRough = Material(Vector3(0.0f, 0.6f, 0.0f),		0.2f, 0.9f, 0.5f, 1.0f, 0.0f, 0.0f, 2.16f);
	Material yellowRough = Material(Vector3(0.5f, 0.5f, 0.0f),		0.2f, 0.6f, 0.7f, 1.0f, 0.0f, 0.0f, 2.61f);

	// Define the world or ground sphere
	Ellipsoid s1(Vector3(0.0f, -100.5f, -2.5f), 100.0f);
	s1.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	s1.SetMaterial(&greenRough);

	// Sphere on left
	Ellipsoid s2(Vector3(-1.0f, 0.0f, -2.5f), 0.5f);
	s2.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	s2.SetMaterial(&lightBlueRough);

	// Sphere in center
	Ellipsoid s3(Vector3(0.0f, 0.0f, -2.5f), 0.5f);
	s3.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	s3.SetMaterial(&yellowRough);

	// Sphere on right
	Ellipsoid s4(Vector3(1.0f, 0.0f, -2.5f), 0.5f);
	s4.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	s4.SetMaterial(&lightBlueSmooth);


	mainScene.AddObject(&s1);
	mainScene.AddObject(&s2);
	mainScene.AddObject(&s3);
	mainScene.AddObject(&s4);
	mainScene.AddLight(&d1);
	mainScene.SetCamera(&mainCamera);

	// get reciprocal of image dimensions
	float invWidth = 1.0f / (float)imageWidth;
	float invHeight = 1.0f / (float)imageHeight;

	// For each Vertical interval of the near hplane
	for (int i = 0; i < imageHeight; i++)
	{
		std::clog << "\rCurrently rendering scanline " << i << " of " << imageHeight << std::flush;
		
		// For each interval of the near plane horizontally
		for (int j = 0; j < imageWidth; j++)
		{
			ColorRGB rayColor(0.0f, 0.0f, 0.0f);
			for (int p = 0; p < raysPerPixel; p++)
			{
				// Calculate screenspace y location
				float screenSpaceY = 1.0f - 2.0f * ((float)i + Random::RandFloat()) * invHeight;
				// Get current pixel in screen space coordinates (in rnage -1 to 1)
				float screenSpaceX = 2.0f * ((float)j + Random::RandFloat()) * invWidth - 1.0f;
				Vector2 screenSpacePos = Vector2(screenSpaceX, screenSpaceY);
				Ray screenRay = mainScene.GetScreenRay(screenSpacePos);
				rayColor += mainScene.CastRay(screenRay, 10);
			}
			rayColor = rayColor * (1.0f / (float)raysPerPixel);

			// The following clamps the color value
			if (rayColor.z > 1)
			{
				rayColor.z = 1;
			}
			if (rayColor.y > 1)
			{
				rayColor.y = 1;
			}
			if (rayColor.x > 1)
			{
				rayColor.x = 1;
			}

			// Write to output stream
			WriteColorRGB(std::cout, rayColor);
		}
		std::cout << std::endl;
	}

	// Set the output stream bugger back to what it was previously
	std::cout.rdbuf(backup);
	return EXIT_SUCCESS;
}