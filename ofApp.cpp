#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofNoFill();
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 240;
	int radius_base = 100;
	int len = 15;
	float hue = 0;
	for (int y = span * 0.5; y < ofGetHeight(); y += span) {

		for (int x = span * 0.5; x < ofGetWidth(); x += span) {

			ofColor color;
			color.setHsb(hue, 230, 255);
			ofSetColor(color);

			ofPushMatrix();
			ofTranslate(x, y);

			vector<glm::vec2> out_vertices;
			vector<glm::vec2> in_vertices;
			for (int deg = 0; deg < 360; deg++) {

				auto noise_point = glm::vec2(x + radius_base * cos(deg * DEG_TO_RAD), y + radius_base * sin(deg * DEG_TO_RAD));
				float noise_len = ofMap(ofNoise(noise_point.x * 0.01, noise_point.y * 0.01, ofGetFrameNum() * 0.01), 0, 1, 5, len);

				float radius = radius_base + noise_len;
				out_vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));

				radius = radius_base - noise_len;
				in_vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}

			ofBeginShape();
			ofVertices(out_vertices);
			ofNextContour(true);
			ofVertices(in_vertices);
			ofEndShape(true);

			ofPopMatrix();

			hue += 25.5;
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}