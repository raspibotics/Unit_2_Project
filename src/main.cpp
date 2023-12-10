#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <complex>
#include "include/Config.hpp"

#ifdef TEST_MAIN
// Declare function prototypes //
int make_window(); // initialize SDL2 subsystems to create window and renderer
int destroy_window(); // destroy window and renderer and quit SDL2 subsystems
int get_audio_input(); // initialize SDL2 audio subsystem and gets audio input from microphone
void audioCallback(void* userdata, Uint8* stream, int len); // callback function for audio device
int stop_audio_input(); // closes the microphone and quits SDL2 audio subsystem
void update_window(std::vector<std::complex<double>>& vector, int size); // updates the window with the audio data from transformed_buffer_complex vector
void display_to_window(std::atomic<bool>& quit); // handles everything needed to create and update window, its done in a different thread
void fft(std::vector<std::complex<double>>& vector); // performs the fft on the audio data



// TODO - Get rid of these, they are declared as macros in config.hpp
// Declare constants //
// const int SAMPLE_RATE = 20480;
// const int SAMPLE_SIZE = 2048;
//declare constants for the sample rate and sample size



// Declare global variables //
SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
//declare the window and renderer pointers, done globally so can be accessed by all functions
SDL_AudioDeviceID microphone = 0;
//declare the microphone ID, done globally so can be accessed by all functions
//so can be closed by the stop_audio_input function
int buffer_int[SAMPLE_SIZE]; // create a buffer of ints to store the audio data for visualisation
std::vector<std::complex<double>> transformed_buffer_complex(SAMPLE_SIZE); // create a buffer of complex doubles to store the audio data for fft



int main(int argc, char* argv[]){ // arguments needed to maintain compatibility with the underlying system and the SDL library's expectations.

    get_audio_input(); // gets audio input from the microphone

    std::atomic<bool> quit(false); // declare an atomic boolean to control window closing
    
    std::thread inputThread(display_to_window, std::ref(quit)); // create a thread to handle the window and renderer
    std::string input; // declare a string to store the input from the user

    while(!quit){ // loop until the user enters 'Close' or closes the window
        std::cout << "Enter 'Close' to close the window: ";
        std::cin >> input;
        if (input == "Close"){
        quit = true;
        
        }else if(quit == true){ //in case the window is closed by pressing the x button, doesnt display anything to console
            
        }
        else{
            std::cout << "Invalid input" << std::endl;
        }
    }
    
    inputThread.join(); // Wait for input thread to finish
    stop_audio_input(); // closes the microphone and quits SDL2 audio subsystem
    SDL_Quit();  
    return 0;
}

int stop_audio_input(){
    SDL_CloseAudioDevice(microphone); // closes the microphone
    return 0;
}

int get_audio_input(){
    SDL_Init(SDL_INIT_AUDIO); // initialize SDL2 audio subsystem

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cout << "SDL could not initialize! SDL audio: " << std::endl;
        return 1;
    }    // check if SDL2 audio subsystem initialized correctly, if not returns 1


    SDL_AudioSpec desiredSpec, obtainedSpec; // declare the desired and obtained audio specs

    desiredSpec.freq = SAMPLE_RATE; // set the desired sample rate
    desiredSpec.format = AUDIO_S16SYS; // set the desired audio format
    desiredSpec.channels = 1; // set the desired number of channels (mono channel)
    desiredSpec.samples = SAMPLE_SIZE; // set the desired sample size
    desiredSpec.callback = audioCallback; // set the desired callback function
    // this audiocallback function is called when the audio device needs more data
    // its in this function that the audio data is processed and used

    microphone = SDL_OpenAudioDevice(NULL, 1, &desiredSpec, &obtainedSpec, 0);

    if (microphone == 0) {
        std::cout << "Failed to open microphone: "<< std::endl;
        return 1;
    } // check if microphone opened correctly, if not returns 1

    SDL_PauseAudioDevice(microphone, 0); // Starts capturing the audio data from the microphone

    return 0;
}

void audioCallback(void* userdata, Uint8* stream, int len) {
    Sint16* buffer = reinterpret_cast<Sint16*>(stream); // cast the stream to a Sint16 pointer
    for(int i = 0; i < SAMPLE_SIZE; i++) {
        transformed_buffer_complex[i] = std::complex<double>(buffer[i]/256,0); 
        // copy the data from the int buffer to the complex double buffer, setting the imaginary part to 0
    }
    fft(transformed_buffer_complex); // perform the fft on the complex double buffer
}


int make_window(){
    SDL_Init(SDL_INIT_VIDEO); // initialize SDL2 video subsystem
    window = SDL_CreateWindow("Audio Visualiser", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 576, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return 0;
}

int destroy_window(){
    SDL_DestroyRenderer(renderer); // destroy renderer
    SDL_DestroyWindow(window); // destroy window
    return 0;
}

void display_to_window(std::atomic<bool>& quit){ 
    make_window(); // creates the window and renderer
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
        update_window(transformed_buffer_complex, SAMPLE_SIZE);
    }
    destroy_window();
}

void update_window(std::vector<std::complex<double>>& vector, int size) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //clears the screen to black and sets the draw colour to white

    for (int i = 0; i <size-2; i++) {
        SDL_RenderDrawLine(renderer, i, (500 - abs(vector[i])), i+1, (500 - abs(vector[i+1])));
        //cycle through the buffer and draw lines between each point
        //the y value is the magnitude of the sample, the x value is the sample number
        //moving accross the screen from left to right
    }
    SDL_RenderPresent(renderer);
    //present the renderer to the window
}

void fft(std::vector<std::complex<double>>& vector) {
    int N = vector.size();
    //gets the the length of the vector
    
    if (N <= 1) {
        return;
    }//if the length is 1 or lower, return
    
    // Split the input into even and odd indices
    std::vector<std::complex<double>> even(N/2);
    std::vector<std::complex<double>> odd(N/2);
    for (int i = 0; i < N/2; i++) {
        even[i] = vector[2*i];
        odd[i] = vector[2*i + 1];
    }
    
    // Recursively perform the fft even and odd indexed values 
    // Splitting the vector into smaller and smaller vectors
    // Until the length is 1, then it returns (the code at start of function)
    fft(even);
    fft(odd);
    
    // Combine the results with the twiddle factors, starting from the smallest vectors
    for (int k = 0; k < N/2; k++) {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * k / N) * odd[k];
        vector[k] = even[k] + t;
        vector[k + N/2] = even[k] - t;
    }
}

#endif
