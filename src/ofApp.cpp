//Ron Stuchevsky | 101188412
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Ray Caster");
    ofSetFrameRate(60);

    //make the spheres
    // x (- left, + right) | y ( + up, - down) | z (- farther away, + closer to camera)
    Sphere s1(glm::vec3(0, 0, -1), 1.0);
    Sphere s2(glm::vec3(-3, 0, -1), 1.0);
    Sphere s3(glm::vec3(5, 3, -0.5), 1.0);
    Sphere s4(glm::vec3(-5, -2, 0), 1.1);
    spheres.push_back(s1);
    spheres.push_back(s2);
    spheres.push_back(s3);
    spheres.push_back(s4);
   
    //from shirley how camera pos and ray per pixel get calced
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 800;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 2.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = glm::vec3(0, 0, 10);

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
    

    for (int y = 0; y < image_height; y++) { //j
        //std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
        for (int x = 0; x < image_width; x++) { //i
            
            //for each pixel make a ray
            auto pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            glm::vec3 pixelColor = ray_color(r);
            
            pix.setColor(x, y, ofFloatColor(pixelColor.x, pixelColor.y, pixelColor.z));
        }
    }
    //std::clog << "\rDone.                 \n";
    renderImg.update();
    renderImg.save("raycast_output.png");
}

glm::vec3 ofApp::ray_color(Ray& r) {
    
    HitRecord tempRecord;
    bool isAnythingHit = false;
    auto closestSoFar = this->infinity;
    for (Sphere& s : this->spheres) {
        if (s.isHit(r, 0, closestSoFar, tempRecord)) {
            
            isAnythingHit = true;
            closestSoFar = tempRecord.t;
            
            this->persistantRecord = tempRecord;
           
        }
    }

    if (isAnythingHit) {
        //currently the normal, next need to do a color calculation based on 3 point
        //+ shadows
        return 0.5 * (this->persistantRecord.normal + glm::vec3(1.0, 1.0, 1.0));
    }
    
    glm::vec3 unit_direction = glm::normalize(r.getDirection());
    auto a = 0.5 * (unit_direction.y + 1.0);
    
    return (1.0 - a) * glm::vec3(1.0, 1.0, 0.0) + a * glm::vec3(0.0, 0.0, 1.0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
   
   
    
    renderImg.draw(0,0);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

