#include "ofApp.h"



float volume = 1.0;
int CurrentNumber = 1;

int GetTrackCount(){
    string path = "/../data";
    ofDirectory dir(path);
    dir.allowExt("wav");
    dir.allowExt("mp3");
    dir.allowExt("flac");
    dir.listDir();
    return dir.size();
}

string ChangeTrack(int TrackNum){
    string path = "/../data";
    ofDirectory dir(path);
    dir.allowExt("wav");
    dir.allowExt("mp3");
    dir.allowExt("flac");
    dir.listDir();
    vector<string> Songlist;
    for(int i = 0; i < dir.size(); i++){
        Songlist.push_back(dir.getName(i));
    }
    for(int i = 0; i < Songlist.size(); i++){
        if(i == (TrackNum-1)){
            return Songlist[i];
        }
    }
    return "Shut up mom I'm making a pizza"; //DUMMY RETURN
}

string track = ChangeTrack(CurrentNumber);

//--------------------------------------------------------------
void ofApp::setup()
{
    sound.loadSound(track);           //Loads a sound file (in bin/data/)
    sound.setLoop(true);              // Makes the song loop indefinitely
    sound.setVolume(volume);          // Sets the song volume
    ofSetBackgroundColor(36, 32, 56); // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update()
{
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate();               // Updates all sound players
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
}

//--------------------------------------------------------------
void ofApp::draw()
{
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */
    int volumepercent = volume * 100;
    ofFill();
    ofSetColor(256);
    ofDrawBitmapString("Volume: " + ofToString(volumepercent) + '%', 0, 30);
    ofFill();
    ofSetColor(256);
    ofDrawBitmapString("Use the '=' and '-' keys to raise and lower volume", 0, 60);
    ofDrawBitmapString("Use the 'd' key to skip songs", 0, 75);
    ofDrawBitmapString("Use the 'r' and 't' keys to record and replay inputs", 0, 90);
    for (int a = -1; a < record.size(); a++)
    {
        if (replaying == true)
        {
            keyPressed(record[a]);
        }
    }
    if (!playing)
    {
        ofFill();
        ofSetColor(256);
        ofDrawBitmapString("Press 'p' to play some music!", 0, 45);
        
    }

    else

    {
        ofFill();
        ofSetColor(256);
        ofDrawBitmapString(("Now playing: " + ofToString(track)), 0, 45);
    }
    if (recording)
        {
            ofSetColor(255);
            ofDrawBitmapString("You are now Recording...", 0, 105);
        }
        if (replaying)
        {
            ofSetColor(255);
            ofDrawBitmapString("You are now Replaying...", 0, 105);
        }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1')
    {
        drawMode1(amplitudes);
    }
    else if (mode == '2')
    {
        drawMode2(amplitudes);
    }
    else if (mode == '3')
    {
        drawMode3(amplitudes);
    }
    else if (mode == '4')
    {
        drawMode4(amplitudes);
    }
}
void ofApp::drawMode1(vector<float> amplitudes)
{
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetColor(255);
    int bands = amplitudes.size();
    double x = 0;
    double initial;
    for (int i = 0; i < bands; i++)
    {
        initial = ofGetWidth() - (ofGetWidth() - x);
        ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)); // Color varies between frequencies
        ofDrawRectangle(initial, ofGetHeight() - 100, (ofGetWidth() / 64), amplitudes[i]);
        x += (ofGetWidth() / 64);
    }
}
void ofApp::drawMode2(vector<float> amplitudes)
{
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++)
    {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / i + 1);
    }
}

void ofApp::drawMode3(vector<float> amplitudes)
{
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
    ofSetColor(255);
    int bands = amplitudes.size();
    double initial;
    double x = 0;
    for (int i = 0; i < bands; i++)
    {
        initial = ofGetHeight() - (ofGetHeight() - x);
        ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)); // Color varies between frequencies
        ofDrawRectangle(ofGetWidth(), initial, amplitudes[i], (ofGetHeight() / 64));
        x += ofGetHeight() / 64;
    }
}
void ofApp::drawMode4(vector<float> amplitudes)
{

    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Custom Visualizer", 0, 15);
    ofNoFill();
    int bands = amplitudes.size();

    //double initial;
    //double x = 0;
    for (int i = 0; i < bands; i++)
    {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawRectangle((ofGetHeight() / 2) + 2, (ofGetWidth() * 2) + 2, (amplitudes[0] / i + 1) * 9, (amplitudes[0] / i + 1 / 64) * 9);
        ofDrawRectangle((ofGetWidth() * 2) + 2, (ofGetHeight() / 2) + 2, (amplitudes[0] / i + 1) * 8, (amplitudes[0] / i + 1 / 64) * 8);
        ofDrawRectangle((amplitudes[0] / i + 1) * 7, (amplitudes[0] / i + 1 / 64) * 7, (ofGetHeight() / 2) + 2, (ofGetWidth() * 2) + 2);
        ofDrawRectangle((amplitudes[0] / i + 1 / 64) * 6, (amplitudes[0] / i + 1) * 6, (ofGetWidth() * 2) + 2, (ofGetHeight() / 2) + 2);
        ofDrawRectangle((ofGetHeight() + 2) + 2, (ofGetWidth() - 2) + 2, (amplitudes[0] / i + 1) * 5, (amplitudes[0] / i + 1 / 64) * 5);
        ofDrawRectangle((ofGetWidth() - 2) + 2, (ofGetHeight() + 2) + 2, (amplitudes[0] / i + 1) * 4, (amplitudes[0] / i + 1 / 64) * 4);
        ofDrawRectangle((amplitudes[0] / i + 1) * 3, (amplitudes[0] / i + 1 / 64) * 3, (ofGetHeight() + 2) + 2, (ofGetWidth() - 2) + 2);
        ofDrawRectangle((amplitudes[0] / i + 1 / 64) * 2, (amplitudes[0] / i + 1) * 2, (ofGetWidth() - 2) + 2, (ofGetHeight() + 2) + 2);
    } // YOUR CODE HERE
}
//--------------------------------------------------------------



//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    if (recording && key != 'r')
    {
        record.push_back(key);
    }

    // This method is called automatically when any key is pressed
    switch (key)
    {
        case 'p':
            if (playing)
            {
                sound.stop();
            }
            else
            {
                sound.play();
            }
            playing = !playing;
            break;
        case '1':
            mode = '1';
            ofBackground(0, 0, 0);
            break;
        case '2':
            mode = '2';
            ofBackground(108, 0, 0);
            break;
        case '3':
            mode = '3';
            ofBackground(0, 0, 74);
            break;
        case '4':
            mode = '4';
            break;
        case '=':
            if (volume < 1.0)
            {
                volume += 0.01;
                sound.setVolume(volume);
            }
            break;
        case '-':
            if (volume > 0)
            {
                volume -= 0.01;
                sound.setVolume(volume);
            }
            break;
        case 'd':
            {
            int TrackCount = GetTrackCount();
            if(CurrentNumber < TrackCount){
                CurrentNumber+=1;
            }
            else if(CurrentNumber == TrackCount){
                CurrentNumber = 1;
            }
            track = ChangeTrack(CurrentNumber);
            if(playing){
                sound.stop();
                sound.loadSound(track);
                sound.play();
            }
            else{
                sound.loadSound(track);
            }
            }
            break;
        case 'r':
            if(recording == false)
            {
                replaying = false;
                recording = true;
                record.clear();
            }
            else
            {
                recording = false;
            }
            break;
        
        case 't':
            if(replaying == false)
            {
                recording = false;
                replaying = true;
                for(int i = 0; i<record.size(); i++){

                    switch (record[i]){
                        case 'p':
                        if (playing)
                        {
                            sound.stop();
                        }
                        else
                        {
                            sound.play();
                        }
                        playing = !playing;
                        break;
                    case '1':
                        mode = '1';
                        ofBackground(0, 0, 0);
                        break;
                    case '2':
                        mode = '2';
                        ofBackground(108, 0, 0);
                        break;
                    case '3':
                        mode = '3';
                        ofBackground(0, 0, 74);
                        break;
                    case '4':
                        mode = '4';
                        break;
                    case '=':
                        if (volume < 1.0)
                        {
                            volume += 0.01;
                            sound.setVolume(volume);
                        }
                        break;
                    case '-':
                        if (volume > 0)
                        {
                            volume -= 0.01;
                            sound.setVolume(volume);
                        }
                        break;
                    case 'd':
                        {
                        int TrackCount = GetTrackCount();
                        if(CurrentNumber < TrackCount){
                            CurrentNumber+=1;
                        }
                        else if(CurrentNumber == TrackCount){
                            CurrentNumber = 1;
                        }
                        track = ChangeTrack(CurrentNumber);
                        if(playing){
                            sound.stop();
                            sound.loadSound(track);
                            sound.play();
                        }
                        else{
                            sound.loadSound(track);
                        }
                        }
                        break;
                    }

                }
            }
            else
            {
                replaying = false;
            }
            break;
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}