// Ron Stuchevsky | 101188412
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("A3-Raycasting");


    // making the spheres
    // x (- left, + right) | y ( + up, - down) | z (- farther away, + closer to camera)
    Sphere s1(glm::vec3(0, 0, -1), 1.1, glm::vec3(1, 1, 0), 2, 0.2); //yellow at the center
    Sphere s2(glm::vec3(0, -2, 3), 0.5, glm::vec3(1,0,0)); //red (only diffuse) at the front bottom
    // green (some where in between shiny and plain) to the right and at the front of yellow which makes it cast a shadow on it.
    Sphere s3(glm::vec3(3, 0, 1), 2, glm::vec3(0, 1, 0),5, 0.1); 
    Sphere s4(glm::vec3(-5, -2, -3), 3, glm::vec3(0, 0, 1), 32, 1.0); //blue (shiny) at the back

    Sphere s5(glm::vec3(0, -6, 0), 4, glm::vec3(0, 1, 1),32,0.5); //cyan 1/2 shiny (only rendering half of it, useful for showing shadow and the raycasting draw order using t)
    spheres.push_back(s1);
    spheres.push_back(s2);
    spheres.push_back(s3);
    spheres.push_back(s4);
    spheres.push_back(s5);

    // make the 2 light sources
    LightSource pointLight(glm::vec3(500, 500, 500),0.7); //1 diagonal strong point light
    LightSource side(glm::vec3(100, 0, 0),0.1); // 1 from the side weaker
    lightSources.push_back(pointLight);
    lightSources.push_back(side);
   
    // following code adopted from Shirley's way of calculating the image and camera position
    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = glm::vec3(viewport_width, 0, 0);
    auto viewport_v = glm::vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
        - glm::vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    
    renderImg.allocate(image_width, image_height, OF_IMAGE_COLOR);
    ofPixels& pix = renderImg.getPixels();
    
    // loop over img pixels
    for (int y = 0; y < image_height; y++) { //j
        for (int x = 0; x < image_width; x++) { //i
            
            // for each pixel make a ray
            auto pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);
            
            glm::vec3 pixelColor = ray_color(r);
            
            pix.setColor(x, y, ofFloatColor(pixelColor.x, pixelColor.y, pixelColor.z));
        }
    }
    renderImg.update();
    renderImg.save("raycast_output.png");
}
/*
Raycast and determine if the ray intersects with any of the spheres, if it is calculate the pixels color,
else set the pixels color to a gradient between yellow and blue since it hit the sky.
*/
glm::vec3 ofApp::ray_color(Ray& r) {
    
    HitRecord tempRecord;
    bool isAnythingHit = false;
    auto closestSoFar = this->infinity;
    // given the ray loop over all the objects in the scene
    for (Sphere& s : this->spheres) {
        if (s.isHit(r, 0, closestSoFar, tempRecord)) {
          
            isAnythingHit = true;
            closestSoFar = tempRecord.t;
            this->persistantRecord = tempRecord;
            
        }
    }
    // compute the color if we hit anything
    if (isAnythingHit) {
        return this->calcThreePointLight(this->persistantRecord);
    }
    // else just sky color
    glm::vec3 unit_direction = glm::normalize(r.getDirection());
    auto a = 0.5 * (unit_direction.y + 1.0);
    
    return (1.0 - a) * glm::vec3(1.0, 1.0, 0.0) + a * glm::vec3(0.0, 0.0, 1.0);
}

/*
Calculate phong three term lighting and shadow test for an intersection
*/
glm::vec3 ofApp::calcThreePointLight(HitRecord& record) {

    glm::vec3 N = glm::normalize(record.normal);
    glm::vec3 V = glm::normalize(camera_center - record.pointColision); // viewpos - intersect point
    glm::vec3 color = this->lightSources[0].ambient * record.objectAlbedo; // first set color to ambient (at minimum will be that)
    
    // loop over the light sources in the scenes to calculate diffuse and specular for all of them and sum them up.
    for (LightSource& src : this->lightSources) {
        // Shadow test first
        // Fire ray towards light source(point light)
        
        glm::vec3 rayDirection = glm::normalize(src.lightPosition - record.pointColision);
        Ray shadowRay(record.pointColision, rayDirection);

        HitRecord tempRecord;
        bool gotBlocked = false;
        
        // If intersects with something closer than the light
        for (Sphere& s : this->spheres) {
                           // min not 0 because then it would instantly detect the sphere itself as obstructing itself and shade, so small offset solves that.
            if (s.isHit(shadowRay, 1e-3f, this->infinity, tempRecord)) {
                // got blocked for this light source
                gotBlocked = true; 
                break;
            }
        }

        if (gotBlocked) {
            continue; // blocked for this light source so continue to the next one, might be able to reach it
        }

        // else not blocked for the light source calc the diffuse and specular terms for the light source
        glm::vec3 L = glm::normalize(src.lightPosition - record.pointColision);

        glm::vec3 R = glm::normalize(-L + (2.0 * N * glm::dot(L, N)));

        float diffuse = std::max(glm::dot(N, L), 0.0f);

        float specular = pow(std::fmax(glm::dot(V, R), 0.0), record.highlightStrengh) * src.specularStrength;
        color += (diffuse * record.objectAlbedo) + (specular * record.shininess);
    }

    return color;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    renderImg.draw(0,0); 
}


