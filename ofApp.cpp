#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	vector<ofColor> color_list = { ofColor(255, 0, 0), ofColor(0, 255, 0), ofColor(0, 0, 255) };

	int param_x = ofMap((ofGetFrameNum() * 8 + ofGetWindowWidth()) % ofGetWindowWidth(), 0, ofGetWindowWidth(), ofGetWindowWidth() * -0.5 - 170, ofGetWindowWidth() * 0.5 + 170);
	int prev_param_x = ofMap(((ofGetFrameNum() - 1) * 8 + ofGetWindowWidth()) % ofGetWindowWidth(), 0, ofGetWindowWidth(), ofGetWindowWidth() * -0.5 - 170, ofGetWindowWidth() * 0.5 + 170);

	for(int y = -150; y <= 150; y += 300){
	
		for (int color_index = 0; color_index < color_list.size(); color_index++) {

			auto noise_seed = ofRandom(1000);

			for (int x = ofGetWindowWidth() * -0.5; x <= ofGetWindowWidth() * 0.5; x += 18) {

				auto noise_value = ofNoise(noise_seed, x * 0.02, ofGetFrameNum() * 0.003);
				auto prev_noise_value = ofNoise(noise_seed, x * 0.02, (ofGetFrameNum() - 1) * 0.003);
				auto param = ofMap(noise_value, 0, 1, -150, 150);
				auto prev_param = ofMap(prev_noise_value, 0, 1, -150, 150);

				auto len = abs(param_x - x);
				auto prev_len = abs(prev_param_x - x);

				param *= len < 170 ? ofMap(len, 0, 170, 1, 0) : 0;
				prev_param *= prev_len < 170 ? ofMap(prev_len, 0, 170, 1, 0) : 0;

				if (param == 0) {

					ofSetColor(color_list[color_index]);
					ofNoFill();
					ofDrawCircle(x, y + param, 7);

					ofFill();
					ofDrawCircle(x, y + param, 7);
				}
				else {

					this->draw_arrow(glm::vec2(x, y + prev_param), glm::vec2(x, y + param), 15, color_list[color_index]);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 next_location, float size, ofColor color) {

	auto angle = std::atan2(next_location.y - location.y, next_location.x - location.x);

	ofSetColor(color, 128);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.8 * cos(angle), size * 0.8 * sin(angle)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) + location);
	ofEndShape(true);

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape(true);

	ofSetColor(color);
	ofNoFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.8 * cos(angle), size * 0.8 * sin(angle)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}