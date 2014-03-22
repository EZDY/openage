#ifndef _ENGINE_AUDIO_RESOURCE_H_
#define _ENGINE_AUDIO_RESOURCE_H_

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include <SDL.h>

namespace engine {
namespace audio {

class Resource {
public:
	Resource() = default;
	virtual ~Resource() = default;

	Resource(const Resource&) = delete;
	Resource &operator=(const Resource&) = delete;

	Resource(Resource&&) = delete;
	Resource &operator=(Resource&&) = delete;

	/**
	 * Returns the resources length in samples.
	 */
	virtual uint32_t get_length() const = 0;

	/**
	 * Returns a pointer to the sample buffer at the given position and the
	 * number of samples that are actually available. If the end of the resource
	 * is reached, 0 will be returned. If the resource is not ready yet, a
	 * nullptr will be returned.
	 * @param position the current position in the resource
	 * @param num_samples the number of samples that should be returned
	 */
	virtual std::tuple<const int16_t*,uint32_t> get_samples(uint32_t position,
			uint32_t num_samples) = 0;
};

class InMemoryResource : public Resource {
private:
	std::unique_ptr<int16_t[]> buffer;
	uint32_t length;

public:
	InMemoryResource(const std::string &path, int format = 0);
	virtual ~InMemoryResource() = default;

	virtual uint32_t get_length() const;	

	virtual std::tuple<const int16_t*,uint32_t> get_samples(uint32_t position,
			uint32_t num_samples);
};

}
}

#endif
