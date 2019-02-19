#ifndef __AUDIO_H
#define __AUDIO_H


const int	SpeakerPin = A2;


void	audioSetup();
void	audioTone(int frequency);
void	audioMute();


#endif // __AUDIO_H
