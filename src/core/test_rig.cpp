#include "test_rig.h"
#include "src/stages/game_stage.h"

void initMetalPlugin(IPluginRegistry& registry);
void initIOSSystemPlugin(IPluginRegistry& registry);
void initSDLSystemPlugin(IPluginRegistry& registry, Maybe<String> cryptKey);
void initSDLInputPlugin(IPluginRegistry& registry);
void initSDLAudioPlugin(IPluginRegistry& registry);

int TestRig::initPlugins(IPluginRegistry& registry)
{
	initMetalPlugin(registry);
#ifdef WITH_IOS
	initIOSSystemPlugin(registry);
#else
	initSDLSystemPlugin(registry, {});
	initSDLInputPlugin(registry);
	initSDLAudioPlugin(registry);
#endif
	return HalleyAPIFlags::Video | HalleyAPIFlags::Audio | HalleyAPIFlags::Input;
}

void TestRig::initResourceLocator(const Path& gamePath, const Path& assetsPath, const Path& unpackedAssetsPath, ResourceLocator& locator)
{
	locator.addPack(Path(assetsPath) / "game.dat");
}

String TestRig::getName() const
{
	return "Halley Test Rig";
}

String TestRig::getDataPath() const
{
	return "HalleyTestRig";
}

bool TestRig::isDevMode() const
{
	return true;
}

std::unique_ptr<Stage> TestRig::startGame(const HalleyAPI* api)
{
	api->video->setWindow(WindowDefinition(WindowType::Window, Vector2i(1280, 720), "HalleyTestRig"));
	api->audio->startPlayback();
	return std::make_unique<GameStage>();
}

HalleyGame(TestRig);
