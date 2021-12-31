#include "play.h"
void play::startpaly() {
	ImageTransformer::convertVideoToAlphabetic(filepath,pages,framenum);
}
play::play(string inpath) {

	filepath = inpath;
	pages.fps = 33;
	pages.row = 1080;
	pages.col = 1920;
}
mediaInfo play::getpages() {
	return pages;
}