# Recursively find all .exe files from current directory
$exeFiles = Get-ChildItem -Path . -Recurse -Filter "*.exe" | Where-Object { $_.Name -notmatch "interactive" }
# Iterate over each .exe file and execute it
foreach ($exe in $exeFiles) {
    Write-Host "Executing: $($exe.Name)" -ForegroundColor Cyan
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
    Write-Host ("-" * 80) -ForegroundColor DarkGray
}