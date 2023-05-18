uniform sampler2D texture;
uniform float transparency;
void main()
{
  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
  gl_FragColor = gl_Color * pixel * vec4(1.0, 1.0, 1.0, transparency);
}
