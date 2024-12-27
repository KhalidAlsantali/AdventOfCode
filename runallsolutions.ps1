# Function to show usage help
function Show-Usage {
    Write-Host "Usage: ./runallsolutions.ps1 [year]" -ForegroundColor Cyan
    Write-Host "  year : (Optional) Year to execute (e.g. 2024) or 'all' for all years"
    Write-Host "  If no argument is provided, shows interactive menu"
    Write-Host "`nExample usage:"
    Write-Host "  ./runallsolutions.ps1 2024    # Run solutions for 2024"
    Write-Host "  ./runallsolutions.ps1 all     # Run solutions for all years"
    Write-Host "  ./runallsolutions.ps1         # Show interactive menu"
}

# Function to execute solutions for a specific year or all years
function Execute-Solutions {
    param (
        [string]$yearPath
    )
    
    # Recursively find all .exe files from specified path
    $exeFiles = Get-ChildItem -Path $yearPath -Recurse -Filter "*.exe" | Where-Object { $_.Name -notmatch "interactive" }
    
    if ($exeFiles.Count -eq 0) {
        Write-Host "No executable files found in $yearPath" -ForegroundColor Yellow
        return
    }
    
    # Iterate over each .exe file and execute it
    foreach ($exe in $exeFiles) {
        # Create a pretty header with the full path
        $fullPath = $exe.FullName
        $headerLength = $fullPath.Length + 10  # Add some padding
        $border = "=" * $headerLength
        
        Write-Host "`n$border" -ForegroundColor DarkCyan
        Write-Host "   $fullPath" -ForegroundColor Cyan
        Write-Host "$border" -ForegroundColor DarkCyan
        
        try {
            # Set the working directory to the location of the .exe file
            Push-Location -Path $exe.DirectoryName
            
            # Execute and measure the command, capturing output
            $output = $null
            $executionTime = Measure-Command {
                $output = & $exe.FullName
                $null = $output # Stop unused variable warning
            }
            
            # Print the output
            if ($output) {
                Write-Host "Output:" -ForegroundColor Yellow
                $output | ForEach-Object { Write-Host $_ }
            }
            
            # Convert the elapsed time to a more readable format
            $timeInMs = $executionTime.TotalMilliseconds
            $color = if ($timeInMs -gt 1000) { "Red" } else { "Green" }
            Write-Host "Execution time: $($timeInMs.ToString('F3')) ms" -ForegroundColor $color
            
            # Restore the previous working directory
            Pop-Location
        } catch {
            Write-Host "Failed to execute: $($exe.Name)" -ForegroundColor Red
            Write-Host "Error: $($_.Exception.Message)" -ForegroundColor Red
        }
        
        # Add a separator line between executions
        Write-Host "`n$border`n" -ForegroundColor DarkGray
    }
}

# Get available years from directory structure
$availableYears = Get-ChildItem -Path . -Directory | Where-Object { $_.Name -match '^\d{4}$' } | Select-Object -ExpandProperty Name

# If no years found, exit
if ($availableYears.Count -eq 0) {
    Write-Host "No year directories found!" -ForegroundColor Red
    exit 1
}

# Check for command line arguments
if ($args.Count -gt 0) {
    # Convert argument to string to ensure ToLower() will work
    $selectedYear = $args[0].ToString()
    
    # Check if help was requested
    if ($selectedYear -eq "-h" -or $selectedYear -eq "--help" -or $selectedYear -eq "/?") {
        Show-Usage
        exit 0
    }
    
    # Handle command line argument
    if ($selectedYear.ToLower() -eq "all") {
        Write-Host "`nExecuting solutions for all years..." -ForegroundColor Green
        foreach ($year in $availableYears) {
            Write-Host "`nProcessing year $year..." -ForegroundColor Cyan
            Execute-Solutions -yearPath "./$year"
        }
        exit 0
    } elseif ($availableYears -contains $selectedYear) {
        Write-Host "`nExecuting solutions for year $selectedYear..." -ForegroundColor Green
        Execute-Solutions -yearPath "./$selectedYear"
        exit 0
    } else {
        Write-Host "Invalid year: $selectedYear" -ForegroundColor Red
        Show-Usage
        exit 1
    }
}

# If no valid command line arguments, show interactive menu
Write-Host "Available years:" -ForegroundColor Cyan
Write-Host "0: All years" -ForegroundColor Yellow
foreach ($year in $availableYears) {
    Write-Host "$year" -ForegroundColor Yellow
}

# Get user input
$selectedYear = Read-Host "`nEnter the year to execute (0 for all years)"

# Validate input
if ($selectedYear -eq "0") {
    Write-Host "`nExecuting solutions for all years..." -ForegroundColor Green
    foreach ($year in $availableYears) {
        Write-Host "`nProcessing year $year..." -ForegroundColor Cyan
        Execute-Solutions -yearPath "./$year"
    }
} elseif ($availableYears -contains $selectedYear) {
    Write-Host "`nExecuting solutions for year $selectedYear..." -ForegroundColor Green
    Execute-Solutions -yearPath "./$selectedYear"
} else {
    Write-Host "Invalid year selected!" -ForegroundColor Red
    exit 1
}