#ifndef ___H__
#define ___H__

namespace PopLib
{
	class ResourceManager;
	class Image;
	class Font;

	Image* AssetsLoadImageById(ResourceManager *theManager, int theId);
	void AssetsReplaceImageById(ResourceManager *theManager, int theId, Image *theImage);
	bool AssetsExtractResourcesByName(ResourceManager *theManager, const char *theName);

	// Main Resources
	bool AssetsExtractMainResources(ResourceManager *theMgr);
	extern Font* BoardScoreFontL1;
	extern Font* BoardScoreFontL2;
	extern Font* BoardScoreFontL3;
	extern Font* TotalScoreFont;
	extern Font* UIFont;
	extern Image* Amber;
	extern Image* ButtonPod1;
	extern Image* ButtonPod2;
	extern Image* ButtonPod3;
	extern Image* ButtonPod4;
	extern Image* ButtonPod5;
	extern Image* Emerald;
	extern Image* GridSurface;
	extern Image* LoadArc;
	extern Image* LoadDock;
	extern Image* LoadingBeam;
	extern Image* LoadingProgressImageRect;
	extern Image* Menu;
	extern Image* MenuBackground;
	extern Image* Ruby;
	extern Image* Sapphire;
	extern Image* TheLaserBeam;
	extern Image* Topaz;
	extern Image* Violet;
	extern Image* White;
	extern Image* score1;
	extern Image* score2;

	enum AssetsResourceId
	{
		LoadDock_ID,
		LoadArc_ID,
		LoadingProgressImageRect_ID,
		MenuBackground_ID,
		LoadingBeam_ID,
		TheLaserBeam_ID,
		Menu_ID,
		score1_ID,
		score2_ID,
		ButtonPod1_ID,
		ButtonPod2_ID,
		ButtonPod3_ID,
		ButtonPod4_ID,
		ButtonPod5_ID,
		GridSurface_ID,
		Amber_ID,
		Emerald_ID,
		Ruby_ID,
		Sapphire_ID,
		Topaz_ID,
		Violet_ID,
		White_ID,
		TotalScoreFont_ID,
		UIFont_ID,
		BoardScoreFontL1_ID,
		BoardScoreFontL2_ID,
		BoardScoreFontL3_ID,
		AssetsRESOURCE_ID_MAX
	};

	Image* AssetsGetImageById(int theId);
	Font* AssetsGetFontById(int theId);
	int AssetsGetSoundById(int theId);

	Image*& AssetsGetImageRefById(int theId);
	Font*& AssetsGetFontRefById(int theId);
	int& AssetsGetSoundRefById(int theId);

	AssetsResourceId AssetsGetIdByImage(Image *theImage);
	AssetsResourceId AssetsGetIdByFont(Font *theFont);
	AssetsResourceId AssetsGetIdBySound(int theSound);
	const char* AssetsGetStringIdById(int theId);
	AssetsResourceId AssetsGetIdByStringId(const char *theStringId);

} // namespace Sexy


#endif
