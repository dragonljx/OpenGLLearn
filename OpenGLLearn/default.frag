#version 330 core
out vec4 FragColor;
in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
//�����
//struct Light {
//	vec3 direction;
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};
//
  
  //���Դ
  struct Light {
        vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{

	// ʹ�õƹ�λ��- ƬԪλ�� ��ȡ���߷���
    vec3 lightDir = normalize(light.position - FragPos);
	float theta     = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	if(theta > light.cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {    

		// ambient ������ = �ƹ���ɫ * ������ɫ
		vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
		// ���������ģ��ƬԪ�ľ���
		float distances = length(light.position - FragPos);
		// ���Դ��˥������
		float attenuation = 1.0 / (light.constant + light.linear * distances + light.quadratic * (distances * distances));
		// diffuse ������ 
		// ��׼������
		vec3 norm = normalize(Normal);
		// ͨ����˷��ߺ͹��߷����ȡ������
		float diff = max(dot(norm, lightDir), 0.0);
		// �ں���������������
		vec3 diffuse = light.diffuse * diff * texture( material.diffuse,TexCoords).rgb;
    
		// specular ���淴��
		// �ӽ�λ�� - ƬԪλ�� ��ȡ�ӽ�����
		vec3 viewDir = normalize(viewPos - FragPos);
		// ��ת�ƹ����� ʹ��reflect ���� �����������
		vec3 reflectDir = reflect(-lightDir, norm);
		// ��֪���в���ͨ�������þ��淴��ֵ����ͨ��pow����ǿ�ȡ�
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

		// �ں����о��淴�����
		vec3 specular = light.specular * spec * texture(material.specular,TexCoords).rgb;  

		//ʹ��˥��ֵ�������� ��ɫ
		//ambient  *= attenuation;  
		diffuse  *= attenuation;
		specular *= attenuation;   

		// �ں����в��� �õ�������ɫ
		vec3 result = ambient + diffuse + specular;
		FragColor = vec4(result, 1.0);
	}
    else 
    {
        // else, use ambient light so scene isn't completely dark outside the spotlight.
        FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
    }
} 