#ifndef VOXEL_STREAM_SCRIPT_H
#define VOXEL_STREAM_SCRIPT_H

#include "voxel_stream.h"
#include <core/object/script_language.h> // needed for GDVIRTUAL macro
#include <core/object/gdvirtual.gen.inc> // Also needed for GDVIRTUAL macro...

// Provides access to a source of paged voxel data, which may load and save.
// Must be implemented in a multi-thread-safe way.
// If you are looking for a more specialized API to generate voxels, use VoxelGenerator.
class VoxelStreamScript : public VoxelStream {
	GDCLASS(VoxelStreamScript, VoxelStream)
public:
	Result emerge_block(zylann::voxel::VoxelBufferInternal &out_buffer, Vector3i origin_in_voxels, int lod) override;
	void immerge_block(zylann::voxel::VoxelBufferInternal &buffer, Vector3i origin_in_voxels, int lod) override;

	int get_used_channels_mask() const override;

protected:
	// TODO Why is it unable to convert `Result` into `Variant` even though a cast is defined in voxel_stream.h???
	//GDVIRTUAL3R(VoxelStream::Result, _emerge_block, Ref<VoxelBuffer>, Vector3i, int)
	GDVIRTUAL3R(int, _emerge_block, Ref<VoxelBuffer>, Vector3i, int)
	GDVIRTUAL3(_immerge_block, Ref<VoxelBuffer>, Vector3i, int)
	GDVIRTUAL0RC(int, _get_used_channels_mask) // I think `C` means `const`?

	static void _bind_methods();
};

#endif // VOXEL_STREAM_SCRIPT_H
