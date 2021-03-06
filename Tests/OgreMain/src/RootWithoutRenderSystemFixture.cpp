/*
 * InitialisedRootFixture.cpp
 *
 *  Created on: 07.01.2017
 *      Author: pavel
 */

#include "RootWithoutRenderSystemFixture.h"

#include <Ogre.h>
#include <OgreDefaultHardwareBufferManager.h>

using namespace Ogre;

void RootWithoutRenderSystemFixture::SetUp()
{
    mFSLayer = new FileSystemLayer(OGRE_VERSION_NAME);
    mRoot = new Root("");
    mHBM = new DefaultHardwareBufferManager;

    MaterialManager::getSingleton().initialise();

    // Load resource paths from config file
    ConfigFile cf;
    String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");

    cf.load(resourcesPath);
    // Go through all sections & settings in the file
    String secName, typeName, archName;
    ConfigFile::SettingsBySection_::const_iterator seci;
    for(seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
        secName = seci->first;
        const ConfigFile::SettingsMultiMap& settings = seci->second;
        ConfigFile::SettingsMultiMap::const_iterator i;
        for (i = settings.begin(); i != settings.end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
}

void RootWithoutRenderSystemFixture::TearDown()
{
    delete mHBM;
    delete mRoot;
    delete mFSLayer;
}
