#include <math.h>
#include <stdio.h>

#define PI 3.141592653589793
#define NUM_RAYS 360  // Number of rays in the circle

typedef struct {
    double x;
    double y;
} Vector2D;

Vector2D player_position = {2.0, 2.0};  // Player's position

double ray_length = 5.0;  // Length of each ray

// Function to cast a ray at a given angle and calculate its end position
Vector2D cast_ray(Vector2D position, double angle, double length) {
    Vector2D ray_end;
    
    // Calculate the direction of the ray using the angle
    double ray_dir_x = cos(angle);
    double ray_dir_y = sin(angle);

    // Calculate the end point of the ray based on the direction and length
    ray_end.x = position.x + ray_dir_x * length;
    ray_end.y = position.y + ray_dir_y * length;

    return ray_end;
}

int main() {
    for (int i = 0; i < NUM_RAYS; i++) {
        // Calculate the angle for each ray (from 0 to 2π radians)
        double angle = (2 * PI / NUM_RAYS) * i;
        
        // Cast the ray and get its end position
        Vector2D ray_end = cast_ray(player_position, angle, ray_length);

        // Print the start and end points of each ray
        printf("Ray %d: Start (%f, %f), End (%f, %f)\n", i, player_position.x, player_position.y, ray_end.x, ray_end.y);
    }

    return 0;
}

