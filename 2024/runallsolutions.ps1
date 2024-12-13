# Define the base directory for the AdventOfCode project
$baseDirectory = "C:\Development\C++\AdventOfCode\2024"

# Recursively find all .exe files
$exeFiles = Get-ChildItem -Path $baseDirectory -Recurse -Filter "*.exe"

# Iterate over each .exe file and execute it
foreach ($exe in $exeFiles) {
    Write-Host "Executing: $($exe.FullName)"
    try {
        # Set the working directory to the location of the .exe file
        Push-Location -Path $exe.DirectoryName

        # Execute the .exe file
        Start-Process -FilePath $exe.FullName -Wait -NoNewWindow

        # Restore the previous working directory
        Pop-Location
    } catch {
        Write-Host "Failed to execute: $($exe.FullName)" -ForegroundColor Red
        Write-Host $_.Exception.Message
    }
}
