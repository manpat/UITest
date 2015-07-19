#ifdef VS

layout(location=0) in vec2 vert;
uniform vec2 pos;
uniform float aspect;

void main(){
	gl_Position = vec4((vert+pos)/vec2(aspect, 1), 0, 1);
}

#else

layout(location=0) out vec4 color;

void main(){
	color = vec4(1,0,0,1);
}

#endif