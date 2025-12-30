$input a_position
$output v_pos

#include <bgfx_shader.sh>

void main()
{
	gl_Position = vec4(POSITION, 1.0);
	v_pos = POSITION;
}