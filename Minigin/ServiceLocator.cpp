#include "ServiceLocator.h"

using namespace dae;

SoundSystem* ServiceLocator::m_pSoundSystem = nullptr;
NullSoundSystem ServiceLocator::m_pNullSoundSystem = NullSoundSystem{};