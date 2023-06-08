uniform float elapsedTime;
uniform sampler2D texture;
void main()
{
  float speedup_factor = 0.2;
  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
  vec4 rgb = vec4(0.5 + 0.5*cos((elapsedTime*speedup_factor)+vec3(0,2,4)), 1.0);
  gl_FragColor = mix(pixel, rgb, 0.6 * pixel.a);
}
