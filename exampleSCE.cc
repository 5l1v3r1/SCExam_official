#include "SCEDetectorConstruction.hh"
#include "SCEActionInitialization.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "FTFP_BERT.hh"
#include "Randomize.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace {
        void PrintUsage() {
                G4cerr << " Usage: " << G4endl;
                G4cerr << " exampleSCE [-ev number of events ] [-en pion energy]" << G4endl;
        }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {

        // Evaluate arguments
        //
        if ( argc > 5 || argc == 1) {
                PrintUsage();
                return 1;
        }

        int nevents;
        G4String energy;
        G4String gev = " GeV";
        for ( G4int i=1; i<argc; i=i+2 ) {
                if      ( G4String(argv[i]) == "-ev" ) nevents = G4UIcommand::ConvertToInt(argv[i+1]);
                else if ( G4String(argv[i]) == "-en" ) energy = argv[i+1] + gev;
                else {
                        PrintUsage();
                        return 1;
                }
        }

        // Choose the Random engine
        //
        G4Random::setTheEngine(new CLHEP::RanecuEngine);

        // Construct the default run manager
        //
        G4RunManager * runManager = new G4RunManager;

        // Set mandatory initialization classes
        //
        auto detConstruction = new SCEDetectorConstruction();
        runManager->SetUserInitialization(detConstruction);

        auto physicsList = new FTFP_BERT;
        runManager->SetUserInitialization(physicsList);

        auto actionInitialization = new SCEActionInitialization();
        runManager->SetUserInitialization(actionInitialization);

        // Initialize G4 kernel
        runManager->Initialize();

        // Get the pointer to the User Interface manager
        auto UImanager = G4UImanager::GetUIpointer();

        // Run commands
        G4String command = "/tracking/verbose 1";
        UImanager->ApplyCommand(command);
        command = "/gun/energy ";
        UImanager->ApplyCommand(command+energy);
        runManager->BeamOn(nevents);


        // Job termination
        // Free the store: user actions, physics_list and detector_description are
        // owned and deleted by the run manager, so they should not be deleted
        // in the main() program !

        delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
