
struct particles {
    float x,y,z,Vx,Vy,Vz;
    unsigned char r,g,b,a;
    float particleSize,weight,angle;
    float life;

    void setPosition(float x,float y,float z)
    {
        particles.x = x;
        particles.y = y;
        particles.z = z;
    }
    void setSpeed(float x, float y, float z)
    {
        particles.Vx = x;
        particles.Vy = y;
        particles.Vz = z;
    }
};
