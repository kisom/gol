#ifndef __AUDIO_H
#define __AUDIO_H

namespace hal {

const int	SpeakerPin = A2;


void	audioSetup();
void	audioTone(int frequency);
void	audioMute();

} // namespace hal
#endif // __AUDIO_H
