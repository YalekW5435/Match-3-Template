#include <PopLib/appbase.hpp>
#include <PopLib/popapp.hpp>
#include <PopLib/resources/resourcemanager.hpp>
#include <PopLib/widget/WidgetManager.hpp>
#include <PopLib/graphics/color.hpp>
#include <numeric>

#include "Assets.hpp"
#include "Match3App.hpp"
#include "TitleScreen.hpp"
#include "LoadingDock.hpp"
using namespace PopLib;

Match3App::Match3App()
{
	
	mWidth = 1600;
	mHeight = 900;

	mRendererAPI = Renderers::SDL;
	mFrameTime = (double) 25 / 3;//If you want your whole game to run at 60fps without relying on VSync, use this.  
								 //It may sound a tad off, but this gets rid of the screen tearing that is visible to
								 //almost every PopCap Game.  I dont know why PopCap never used this trick.  
								 // Only downside you will need to change your movement and animation speeds down.
	
	mAutoEnable3D = true;
	// REALLY IMPORTANT: Please do add 3D acceleration, even if your GPU does NOT support it.  This way, if the game
	// detects the use of a high performance gpu, you can guarantee the best graphics on another PC.  It will also allow
	// for the mFrameTime trick take place in all of the widget's, making things feel as smooth as butter.  
	
	//Title our game and add it to the registry.  
	mTitle = "Match 3 Template 0.5";
	mRegKey = "PopCap Fan Games/PopLib/match 3 template";
	
	
	
	mTitleScreen = nullptr;
}

Match3App::~Match3App()
{
	if (mTitleScreen)
		mWidgetManager->RemoveWidget(mTitleScreen);
	delete mTitleScreen;

}


void Match3App::InitHook()
{
	
	//Call parent class inheritances.  
	// I use PopApp instead of AppBase.  The PopApp class allows AppBase to be processed in as little time as possible.  Theres also some interesting stuff found
	//in the examples that can be found in the examples folder, such as Discord RPC and steam API.
	PopApp::InitHook();

		/*100 ticks per second is useful for high refresh rates, but on some monitors theres a noticeable refresh
			"adjustment" in the form of "pacing". This causes a noticeable stutter or judder, which can hinder smooth visuals. This
			was noticed in all of PopCap's games, when 100 ticks was used, and only 60 hz refresh rates were used on-par with the
			60 hz/120 hz powerbricks on most monitors. */
	
	LoadResourceManifest();


	//To make things simpler im just going to load all the resources into the loading time as a single group, as most match 3 games
	//are essentially the same throughout all the modes and use identical assets.  
	if (!mResourceManager->LoadResources("Main"))

	{
		mLoadingFailed = true;
		ShowResourceError(true);
		return;
	}
	if (!AssetsExtractMainResources(mResourceManager))

	{
		mLoadingFailed = true;
		ShowResourceError(true);
		return;
	}
	
	
}
void Match3App::LoadingThreadProc()
{
	PopApp::LoadingThreadProc();
	mResourceManager->StartLoadResources("Main");

	while (mResourceManager->LoadNextResource())
	{
		mCompletedLoadingThreadTasks++; // tracks the no. of completed tasks and gives the percentage of loading bar
		if (mShutdown)					// in case of error this variable is automatically set to True
			return;
	}

	if (mResourceManager->HadError() || !AssetsExtractMainResources(mResourceManager))
	{
		ShowResourceError(false);
		mLoadingFailed = true;
		return;
	}

	
	// Add our title screen from titlescreen.hpp and cpp.
	mTitleScreen = new TitleScreen(this);
	mTitleScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mTitleScreen);

	

}
void Match3App::LoadingThreadCompleted()
{
	PopApp::LoadingThreadCompleted();
	
	

}
