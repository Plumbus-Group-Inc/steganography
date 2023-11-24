#include <stdexcept>
#include <sstream>
#include <AudioFile.h>

#include "wav.hpp"

namespace mmht {
    
class WAVLoader : public ILoader {
public:
    WAVLoader(fs::path const& path);
    ~WAVLoader() override = default;

    Data loadData() override;

private:
    AudioFile<float> m_audioFile;
};

WAVLoader::WAVLoader(fs::path const& path) {
    if(path.extension() != "wav") {
        throw std::invalid_argument("ne po ustavu");
    }

    if(!m_audioFile.load(path.string())) {
        std::stringstream errStream;
        errStream << "Failed to load wav file \'" << path << "\'";

        throw std::runtime_error(errStream.str());
    }
}

Data WAVLoader::loadData() {
    std::size_t freq = static_cast<std::size_t>(m_audioFile.getSampleRate());
    std::size_t channels = 
        static_cast<std::size_t>(m_audioFile.getNumChannels());
    std::size_t samples = 
        static_cast<std::size_t>(m_audioFile.getNumSamplesPerChannel());
    std::size_t depth = static_cast<std::size_t>(m_audioFile.getBitDepth());

    if(freq == 0 || channels == 0 || samples == 0 || depth == 0) {
        std::stringstream errStream;
        errStream << "Invalid WAV file data: sample-rate = " << freq << 
            ", channels = " << channels << ", samples-per-channel = " <<
            samples << ", depth = " << depth;

        throw std::runtime_error(errStream.str());
    }

    Data data;
    data.freq = freq;
    data.channels = channels;
    data.left = m_audioFile.samples[0];

    if(channels == 2) {
        data.right = m_audioFile.samples[1];
    }

    return data;
}

class WAVSaver : public ISaver {
public:
    WAVSaver(fs::path const& path);
    ~WAVSaver() override = default;

    void saveData(Data const& data) override;

private:
    fs::path m_path;
    AudioFile<float> m_audioFile;
};


WAVSaver::WAVSaver(fs::path const& path) : m_path(path) {
    if(path.extension() != "wav") {
        throw std::invalid_argument("ne po ustavu");
    }
}

void WAVSaver::saveData(Data const& data) {
    if(data.freq == 0 || data.channels == 0 || data.depth == 0) {
        std::stringstream errStream;
        errStream  << "Invalid WAV file sample-rate = " <<
            data.freq << " or channels = " << data.channels <<
            " or depth = " << data.depth;

        throw std::invalid_argument(errStream.str());
    }

    if((data.channels == 1 && data.left.size() == 0) ||
       (data.channels == 2 && data.left.size() == 0 ||
            (data.left.size() != data.right.size()))) {
        throw std::invalid_argument("WAV file channels data corrupted");
    }

    m_audioFile.setSampleRate(static_cast<std::uint32_t>(data.freq));
    m_audioFile.setNumSamplesPerChannel(static_cast<int>(data.channels));
    m_audioFile.setBitDepth(static_cast<int>(data.depth));

    m_audioFile.setAudioBufferSize(data.channels, data.left.size());
    m_audioFile.samples[0] = data.left;
    
    if(data.channels == 2) {
        m_audioFile.samples[1] = data.right;
    }

    if(!m_audioFile.save(m_path.string())) {
        std::stringstream errStream;
        errStream << "Failed to save WAV file at " << m_path;

        throw std::runtime_error(errStream.str());
    }
}

}

