void MAIN()
{
    float clr = 0.25 - ((UV0.x - 0.5) * (UV0.x - 0.5) + (UV0.y - 0.5) * (UV0.y - 0.5));
    BASE_COLOR = vec4(clr*0.8, clr*0.5, clr*0.8, 1.0);
}
