#include <eemagine/sdk/factory.h> // SDK header
#include <eemagine/sdk/wrapper.cc> // Wrapper code to be compiled.
// For sleeping
#include <chrono>
#include <thread>
#include <iostream> // console io
// #include <conio.h> // For _kbhit();

int main(int argc, char **argv)
{
    using namespace eemagine::sdk;
    eemagine::sdk::factory fact;
    eemagine::sdk::amplifier* amp = fact.getAmplifier(); // Get an amplifier
    eemagine::sdk::stream* eegStream = amp->OpenEegStream(500); // The sampling rate is the only argument needed

    while (true) // Loop until any key gets pressed
    { 
        eemagine::sdk::buffer buf = eegStream->getData(); // Retrieve data from stream
        std::cout << "Samples read: " << buf.getSampleCount() << std::endl;
        for (size_t chan = 0; chan < buf.getChannelCount(); chan++)
        {
            for (size_t sample = 0; sample < buf.getSampleCount(); sample++)
            {
                std::cout << " " << buf.getSample(chan, sample);
            }
            std::cout << std::endl;

        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Need to sleep less than 1s otherwise data may be lost
    }
// release Resources
    delete eegStream;
    delete amp;
    return 0;
}
