#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include "lasreader.hpp"

void CreatePointCloud();
void ReadPCD();
void ReadLas();

int main() {
    //CreatePointCloud();

    ReadLas();

    return 0;
}

void ReadLas() {
    std::string strLasPath = "/home/zzw/opt/lastools/LASzip/example/5points_14.las";
    LASreadOpener lasReadOpener;
    lasReadOpener.set_file_name(strLasPath.data());
    LASreader* lasReader = lasReadOpener.open(strLasPath.data(), FALSE);
    if (lasReader == NULL) {
        return;
    }

    std::vector<pcl::PointXYZ> vPoints;

#pragma region Las information
    int majorVersion = lasReader->header.version_major;
    int minorVersion = lasReader->header.version_minor;
    int pointDataFormat = lasReader->header.point_data_format;
    int pointAmount = lasReader->header.number_of_point_records;
    double maxX = lasReader->header.max_x;
    double minX = lasReader->header.min_x;
    double maxY = lasReader->header.max_y;
    double minY = lasReader->header.min_y;
    double maxZ = lasReader->header.max_z;
    double minZ = lasReader->header.min_z;
    double deltaX = maxX - minX;
    double deltaY = maxY - minY;
    double deltaZ = maxZ - minZ;
    double xOffset = lasReader->header.x_offset;
    double yOffset = lasReader->header.y_offset;
    double zOffset = lasReader->header.z_offset;
    double xScale = lasReader->header.x_scale_factor;
    double yScale = lasReader->header.y_scale_factor;
    double zScale = lasReader->header.z_scale_factor;
#pragma endregion
    while (lasReader->read_point()) {
        LASpoint &pointReader = lasReader->point;

        pcl::PointXYZ p;
        p.x = pointReader.get_x();
        p.y = pointReader.get_y();
        p.z = pointReader.get_z();
        /*p.intensity = pointReader.get_intensity();
        p.pointSourceID = pointReader.get_point_source_ID();
        p.GPStime = pointReader.get_gps_time();
        p.r = pointReader.get_R();
        p.g = pointReader.get_G();
        p.b = pointReader.get_B();
        p.classification = pointReader.get_classification();*/

        vPoints.push_back(p);
    }

    lasReader->close();
    delete lasReader;
    lasReader = nullptr;
}

void CreatePointCloud() {
    pcl::PointCloud<pcl::PointXYZ> cloud;
    // 创建点云
    cloud.width = 5;
    cloud.height = 1;
    cloud.is_dense = false;
    cloud.points.resize(cloud.width * cloud.height);
    for (size_t i = 0; i < cloud.points.size(); ++i)
    {
    	cloud.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
    	cloud.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
    	cloud.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
    }
    pcl::io::savePCDFileASCII("test_pcd.pcd", cloud);
    std::cerr << "Saved " << cloud.points.size() << " data points to test_pcd.pcd." << std::endl;
    for (size_t i = 0; i < cloud.points.size(); ++i)
    {
    	std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;
    }
}

void ReadPCD()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>); // 创建点云（指针）

    if (pcl::io::loadPCDFile<pcl::PointXYZ>("data\\rabbit.pcd", *cloud) == -1) //* 读入PCD格式的文件，如果文件不存在，返回-1
    {
        PCL_ERROR("Couldn't read file test_pcd.pcd \n"); //文件不存在时，返回错误，终止程序。
        return;
    }
    std::cout << "Loaded "
              << cloud->width * cloud->height
              << " data points from test_file.pcd with the following fields: "
              << std::endl;
    for (size_t i = 0; i < cloud->points.size(); ++i)
    {
        std::cout << "    " << cloud->points[i].x
                  << " " << cloud->points[i].y
                  << " " << cloud->points[i].z << std::endl;
    }
}