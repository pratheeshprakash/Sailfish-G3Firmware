#include "Timeout.hh"
#include "ExtruderBoard.hh"

Timeout::Timeout() : active_(false), elapsed_(false) {}

Timeout::Timeout(int32_t duration_micros) {
	active_ = true;
	elapsed_ = false;
	end_stamp_micros_ = ExtruderBoard::getBoard().getCurrentMicros() + duration_micros;
}

bool Timeout::hasElapsed() {
	if (active_ && !elapsed_) {
		if ((end_stamp_micros_ - ExtruderBoard::getBoard().getCurrentMicros()) <= 0) {
			active_ = false;
			elapsed_ = true;
		}
	}
	return elapsed_;
}

void Timeout::abort() {
	active_ = false;
}
