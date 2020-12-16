default:
	mkdir -p bin
	g++ `pkg-config --cflags gtkmm-3.0` -o ./bin/mck-synth ./src/main.cpp ./src/AudioHandler.cpp ./src/MidiHandler.cpp ./src/SettingsWindow.cpp -lrtaudio -lrtmidi `pkg-config --libs gtkmm-3.0`
