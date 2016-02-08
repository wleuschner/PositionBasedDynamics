#ifndef MATERIAL_H
#define MATERIAL_H
#include<QVector3D>

class Material
{
private:
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;
public:
    Material();
    Material(const QVector3D& ambient,const QVector3D& diffuse,const QVector3D& specular,float shininess);
    QVector3D getSpecular() const;
    void setSpecular(const QVector3D &value);
    QVector3D getDiffuse() const;
    void setDiffuse(const QVector3D &value);
    QVector3D getAmbient() const;
    void setAmbient(const QVector3D &value);
    float getShininess() const;
    void setShininess(float value);
};

#endif // MATERIAL_H
