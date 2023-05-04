#ifndef VOXEL_BLOCKY_ATTRIBUTE_H
#define VOXEL_BLOCKY_ATTRIBUTE_H

#include "../../../util/godot/classes/resource.h"
#include "../../../util/span.h"
#include <vector>

namespace zylann::voxel {

// Attribute that can be attached to a VoxelBlockyType.
// It has a unique name and can take two or more positive values. Values can be named.
class VoxelBlockyAttribute : public Resource {
	GDCLASS(VoxelBlockyAttribute, Resource)
public:
	static const int MAX_VALUES = 256;

	virtual StringName get_attribute_name() const;

	// TODO Actually this returns the max value +1. This is not the total amount of values the attribute takes!
	int get_value_count() const;

	int get_default_value() const;
	void set_default_value(int value);

	// TODO -1 means "not found", but I don't like it...
	int get_value_from_name(StringName name) const;

	StringName get_name_from_value(int v) const;
	Span<const uint8_t> get_used_values() const;
	bool is_value_used(int v) const;
	// bool has_named_values() const;

	inline bool is_rotation() const {
		return _is_rotation;
	}

	// virtual int get_order() const;

	// TODO Modifying models from a function of attributes is actually not a good idea... not all cases work.
	// virtual void apply(VoxelBlockyModel &model, int value);

	static void sort_by_name(Span<Ref<VoxelBlockyAttribute>> attributes);
	static void sort_by_name(Span<StringName> attributes);
	static void sort_by_name(Span<std::pair<StringName, uint8_t>> attributes);

private:
	static void _bind_methods();

protected:
	StringName _name;
	uint8_t _default_value = 0;
	bool _is_rotation = false;
	std::vector<StringName> _value_names;

	// Attributes don't necessarily use all the values in their range, some can be unused. But they should not take part
	// into the baking process (no "holes").
	std::vector<uint8_t> _used_values;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// `axis`
class VoxelBlockyAttributeAxis : public VoxelBlockyAttribute {
	GDCLASS(VoxelBlockyAttributeAxis, VoxelBlockyAttribute)
public:
	enum Axis { AXIS_X, AXIS_Y, AXIS_Z, AXIS_COUNT };

	VoxelBlockyAttributeAxis();

	void set_horizontal_only(bool h);
	bool is_horizontal_only() const;

private:
	void update_values();

	static void _bind_methods();

	bool _horizontal_only = false;
	// TODO Corresponding ortho rotations
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// `direction`
class VoxelBlockyAttributeDirection : public VoxelBlockyAttribute {
	GDCLASS(VoxelBlockyAttributeDirection, VoxelBlockyAttribute)
public:
	enum Direction { //
		DIR_NEGATIVE_X,
		DIR_POSITIVE_X,
		DIR_NEGATIVE_Y,
		DIR_POSITIVE_Y,
		DIR_NEGATIVE_Z,
		DIR_POSITIVE_Z,
		DIR_COUNT
	};

	VoxelBlockyAttributeDirection();

	void set_horizontal_only(bool h);
	bool is_horizontal_only() const;

private:
	void update_values();

	static void _bind_methods();

	bool _horizontal_only = false;
	// TODO Corresponding ortho rotations
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// `rotation`
class VoxelBlockyAttributeRotation : public VoxelBlockyAttribute {
	GDCLASS(VoxelBlockyAttributeRotation, VoxelBlockyAttribute)
public:
	VoxelBlockyAttributeRotation();

	void set_horizontal_roll_enabled(bool enable);
	bool is_horizontal_roll_enabled() const;

private:
	void update_values();

	static void _bind_methods();

	bool _horizontal_roll_enabled = false;
	// TODO Corresponding ortho rotations
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// class VoxelBlockyAttributeCustom : public VoxelBlockyAttribute {
// 	GDCLASS(VoxelBlockyAttributeCustom, VoxelBlockyAttribute)
// public:
// 	void set_value_count(int count);
// 	void set_value_name(int index, StringName name);
// 	void set_default_value(int v);

// private:
// 	static void _bind_methods();
// };

} // namespace zylann::voxel

VARIANT_ENUM_CAST(zylann::voxel::VoxelBlockyAttributeAxis::Axis);
VARIANT_ENUM_CAST(zylann::voxel::VoxelBlockyAttributeDirection::Direction);

#endif // VOXEL_BLOCKY_ATTRIBUTE_H
