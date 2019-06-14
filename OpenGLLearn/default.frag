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
//定向光
//struct Light {
//	vec3 direction;
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};
//
  
  //点光源
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

	// 使用灯光位置- 片元位置 获取光线方向
    vec3 lightDir = normalize(light.position - FragPos);
	float theta     = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	if(theta > light.cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {    

		// ambient 环境光 = 灯光颜色 * 材质颜色
		vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
		// 计算光点距离模型片元的距离
		float distances = length(light.position - FragPos);
		// 点光源的衰减函数
		float attenuation = 1.0 / (light.constant + light.linear * distances + light.quadratic * (distances * distances));
		// diffuse 漫反射 
		// 标准化法线
		vec3 norm = normalize(Normal);
		// 通过点乘法线和光线方向获取漫反射
		float diff = max(dot(norm, lightDir), 0.0);
		// 融合所有漫反射属性
		vec3 diffuse = light.diffuse * diff * texture( material.diffuse,TexCoords).rgb;
    
		// specular 镜面反射
		// 视角位置 - 片元位置 获取视角向量
		vec3 viewDir = normalize(viewPos - FragPos);
		// 反转灯光向量 使用reflect 函数 求出反射向量
		vec3 reflectDir = reflect(-lightDir, norm);
		// 已知所有参数通过点乘求得镜面反射值，并通过pow调节强度。
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

		// 融合所有镜面反射参数
		vec3 specular = light.specular * spec * texture(material.specular,TexCoords).rgb;  

		//使用衰减值处理所有 颜色
		//ambient  *= attenuation;  
		diffuse  *= attenuation;
		specular *= attenuation;   

		// 融合所有参数 得到最终颜色
		vec3 result = ambient + diffuse + specular;
		FragColor = vec4(result, 1.0);
	}
    else 
    {
        // else, use ambient light so scene isn't completely dark outside the spotlight.
        FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
    }
} 