float RelativeErr(float base, float val)
{
    float out = 0;

    //exclude very small numbers near zero
    if (base <= 1e-7)
    {
        out = 1;
    }
    else
    {
        out = (val - base) / base;
    }

    return out;
}
