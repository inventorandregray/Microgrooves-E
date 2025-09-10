# Microgrooves-E 🎶

**Microgrooves-E** is an open-source multimedia system designed to simulate audio and video playback/recording with polyphonic support and basic EQ features. Originally engineered with early mobile hardware constraints in mind.

---

## ✨ Features

### 1. Full Album Playback
- Supports multiple tracks per album, sequential playback  
- Optional **shuffle** and **loop** functionality  

### 2. Audio & Video Recording / Playback
- `recordAudio()` and `recordVideo()` simulate recording streams from microphone and camera  
- Playback integrates with **polyphonic simulation**  

### 3. Polyphonic Audio
- Multiple tracks can be "played" simultaneously  
- Implemented using **time-slicing** (as per IBM Simon hardware constraints)  

### 4. EQ Adjustments
- **Bass** and **Treble** adjust track playback volume  

### 5. Hardware Simulation
- `hwPlayAudio()` represents **DAC + timer output** to Simon speaker hardware  

### 6. Open Source Release
- Fully modular **C/C++ code**  

---

© Andre Gray 1998, released to the public.
