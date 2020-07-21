#ifndef GEOM_H_
#define GEOM_H_

#include "TGeometry.h"
#include "TGeoManager.h"

namespace bdm {

  inline TGeoManager* BuildTwoRoom() {

      TGeoManager *geom = new TGeoManager("apartment", "two room apartment on the second floor");

      // materials
      TGeoMaterial *Vacuum = new TGeoMaterial("vacuum", 0, 0, 0);
      TGeoMaterial *Fe = new TGeoMaterial("Fe",55.845,26,7.87);
      TGeoMaterial *Cement = new TGeoMaterial("Cement",55.845,26,7.87);
      // media
      TGeoMedium *Air = new TGeoMedium("Air", 0, Vacuum);
      TGeoMedium *Concrete = new TGeoMedium("concrete", 0, Cement);
      TGeoMedium *Iron = new TGeoMedium("Iron", 0, Fe);

      // simulation volume - 11m * 6m * 3.5m
      TGeoVolume *sim_space = gGeoManager->MakeBox("sim_space", Air, 1100, 600, 350);
      gGeoManager->SetTopVolume(sim_space);
      gGeoManager->SetTopVisible(0);


      TGeoVolume *mBlocks;

      // apartment - 10m * 5m * 2.5m
      // outside walls
      mBlocks = geom->MakeBox("floor_roof", Concrete, 1000, 500, 5);
      mBlocks->SetLineColor(kBlack);
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(0, 0, -250));
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(0, 0, 250));

      mBlocks = geom->MakeBox("wall_length", Concrete, 1000, 5, 250);
      mBlocks->SetLineColor(kBlack);
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(0, -500, 0));
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(0, 500, 0));

      mBlocks = geom->MakeBox("wall_width", Concrete, 5, 500, 250);
      mBlocks->SetLineColor(kBlack);
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(-1000, 0, 0));
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(1000, 0, 0));

      // inside wall
      // mBlocks = geom->MakeBox("inside_wall", Concrete, 5, 500, 250);
      // mBlocks->SetLineColor(kBlack);
      // sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(0, 0, 0));
      mBlocks = geom->MakeBox("wall_inside_sides", Concrete, 5, 200, 250);
      mBlocks->SetLineColor(kBlack);
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(0, 300, 0));
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(0, -300, 0));
      mBlocks = geom->MakeBox("wall_inside_top", Concrete, 5, 100, 50);
      mBlocks->SetLineColor(kBlack);
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(0, 0, 200));

      // windows
      mBlocks = geom->MakeBox("window1", Iron, 100, 5, 100);
      mBlocks->SetLineColor(kGray);
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(500, -500, 25));

      mBlocks = geom->MakeBox("window2", Iron, 100, 5, 100);
      mBlocks->SetLineColor(kGray);
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(-500, -500, 25));

      // doors
      mBlocks = geom->MakeBox("outside_door", Iron, 5, 100, 200);
      mBlocks->SetLineColor(kGray);
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(-1000, 0, -49));

      mBlocks = geom->MakeBox("inside_door", Iron, 5, 100, 200);
      mBlocks->SetLineColor(kGray);
      sim_space->AddNodeOverlap(mBlocks, 1, new TGeoTranslation(0, 0, -49));


      // display geometry
      geom->CloseGeometry();
      // sim_space->Draw();

      std::cout << "geom construction done" << std::endl;

      // return sim_space;
      return geom;

  } // end BuildTwoRoom


  // return wall distance from A, in direction A->B
  // return infinity if no wall is between A and B
  inline double DistToWall(Double3 positionA, Double3 positionB) {
    double dAB[3];
    for (int i=0; i<3; ++i) {
      dAB[i] = positionB[i] - positionA[i];
    }
    double distAB = std::sqrt(dAB[0]*dAB[0] + dAB[1]*dAB[1] + dAB[2]*dAB[2]);
    // normalize the direction
    for (int i=0; i<3; ++i) {
      dAB[i] /= distAB;
    }
    // initialize starting point in the position of A and starting direction shooting towards B
    double A[3];
    for (int i=0; i<3; ++i) A[i] = positionA[i];
    gGeoManager->InitTrack(A, dAB);
    // geo->InitTrack(positionA, dAB);
    // Shoot the ray towards B and check if it hits something in between
    // auto node = gGeoManager->FindNextBoundary();
    double step = gGeoManager->GetStep();
    // distance from positionA
    // std::cout << "We hit " << node->GetName() << " at distance " << step;
    return step;
  } // end DistToWall

  // inline bool IsObjInbetween(double positionA[3], double positionB[3]) {
  //   double dAB[3];
  //   for (int i=0; i<3; ++i) {
  //     dAB[i] = positionB[i] - positionA[i];
  //   }
  //   double distAB = std::sqrt(dAB[0]*dAB[0] + dAB[1]*dAB[1] + dAB[2]*dAB[2]);
  //   // normalize the direction
  //   for (int i=0; i<3; ++i) {
  //     dAB[i] /= distAB;
  //   }
  //
  //   // initialize starting point in the position of A and starting direction shooting towards B
  //   gGeoManager->InitTrack(positionA, dAB);
  //   // geo->InitTrack(positionA, dAB);
  //   // Shoot the ray towards B and check if it hits something in between
  //   auto node = gGeoManager->FindNextBoundary();
  //   double step = gGeoManager->GetStep();
  //   if (step < distAB) {
  //     return true;
  //   }
  //   return false;
  // } // end IsObjInbetween


}  // namespace bdm

#endif // GEOM_H_
