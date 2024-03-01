document.addEventListener('DOMContentLoaded', () => {
    const completeButton = document.getElementById('complete-workflow');
    const outputArea = document.querySelector('.output-area');
    const resetOutputButton = document.getElementById('reset-output');
    const resetButton = document.getElementById('reset-workflow');
    const toggleSidebarButton = document.getElementById('toggle-sidebar');
    const sidebar = document.querySelector('.sidebar');
    const clearSearchButton = document.getElementById('clear-search');
    const searchInput = document.getElementById('search');
    const searchButton = document.getElementById('search-button');

    const toggleSubListVisibility = (workflowItem, isSelected) => {
        const sublist = workflowItem.querySelector('.sub-list');
        sublist.style.display = isSelected ? 'block' : 'none';
    };

    const checkAndToggleCompleteButtonVisibility = () => {
        const anySelected = document.querySelector('.workflow-item.selected');
        completeButton.style.display = anySelected ? 'block' : 'none';
    };

    const checkAndToggleWorkflowButtonsVisibility = () => {
        const anySelected = document.querySelector('.workflow-item.selected');
        completeButton.style.display = anySelected ? 'block' : 'none';
        resetButton.style.display = anySelected ? 'block' : 'none'; // Add this line
    };

    const clearSelections = (exceptItem = null) => {
        document.querySelectorAll('.workflow-item.selected').forEach(item => {
            if (item !== exceptItem) {
                item.classList.remove('selected');
                item.style.border = "";
                toggleSubListVisibility(item, false);
            }
        });
        document.querySelectorAll('.workflow-sub-item.selected').forEach(item => {
            if (item !== exceptItem) {
                item.classList.remove('selected');
                item.style.backgroundColor = "";
            }
        });
        if (!exceptItem) {
            outputArea.textContent = "";
        }
    };

    let isFlowOutputShown = false;
    let isResetOutputShown = false;

    completeButton.style.display = 'none';
    resetButton.style.display = 'none';

    sidebar.classList.add('sidebar-hidden');
    toggleSidebarButton.classList.remove('toggle-sidebar-active');

    function updateSublist(files) {
        const workflowItems = document.querySelectorAll('.workflow-item');
        let mechanicsSublist, thermalPhysicsSublist;

        workflowItems.forEach(item => {
            if (item.textContent.includes('Mechanics')) {
                mechanicsSublist = item.querySelector('.sub-list');
            } else if (item.textContent.includes('Thermal Physics')) {
                thermalPhysicsSublist = item.querySelector('.sub-list');
            }
        });

        function populateSublist(sublist, conditionFunc) {
            sublist.innerHTML = '';
            files.filter(conditionFunc).forEach(file => {
                let listItem = document.createElement('li');
                listItem.className = 'workflow-sub-item';
                listItem.textContent = file;
                sublist.appendChild(listItem);

                listItem.addEventListener('click', (e) => {
                    e.stopPropagation();
                    const isSelected = !listItem.classList.contains('selected');
                    document.querySelectorAll('.workflow-sub-item.selected').forEach(selectedItem => {
                        if (selectedItem !== listItem) {
                            selectedItem.classList.remove('selected');
                            selectedItem.style.backgroundColor = "";
                        }
                    });

                    listItem.classList.toggle('selected', isSelected);
                    listItem.style.backgroundColor = isSelected ? "purple" : "";

                    if (isSelected) {
                        window.electronAPI.sendMessage('readFileContent', file);
                    } else {
                        outputArea.textContent = "";
                    }
                });
            });
        }

        if (mechanicsSublist) {
            populateSublist(mechanicsSublist, file => file.startsWith('processed_force_data') || file.startsWith('processed_weight_data'));
        }
        if (thermalPhysicsSublist) {
            populateSublist(thermalPhysicsSublist, file => file.startsWith('processed_latent_heat_data'));
        }
    }

    function toggleSearchButtonVisibility() {
        // Check if the search input has text
        if (searchInput.value.trim().length > 0) {
            // If there is text, show the search button
            searchButton.style.display = 'inline-block'; // or 'block' depending on your layout
        } else {
            // If there is no text, hide the search button
            searchButton.style.display = 'none';
        }
    }

    function toggleClearSearchButtonVisibility() {
        const searchResultsArea = document.querySelector('.search-results-area');
        const clearSearchButton = document.getElementById('clear-search');
        
        // Check if the search results area has content (child nodes)
        if (searchResultsArea.innerHTML.trim() !== '') {
            // If there is content, make the clear search button visible
            clearSearchButton.style.display = 'block';
        } else {
            // If there is no content, hide the clear search button
            clearSearchButton.style.display = 'none';
        }
    }

    // Initially call the toggle function in case there's already text filled in (e.g., by browser autofill)
    toggleSearchButtonVisibility();
    toggleClearSearchButtonVisibility();

    // Add event listener for input changes on the search input
    searchInput.addEventListener('input', toggleSearchButtonVisibility);

    completeButton.addEventListener('click', () => {
        window.electronAPI.sendMessage('openApplication');
    });

    resetOutputButton.addEventListener('click', () => {
        isResetOutputShown = !isResetOutputShown;
        if (isResetOutputShown) {
            window.electronAPI.sendMessage('readResetLog');
        } else {
            document.querySelector('.output-area').textContent = '';
        }
    });

    toggleSidebarButton.addEventListener('click', () => {
        sidebar.classList.toggle('sidebar-hidden');

        // Toggle the class based on the sidebar visibility
        toggleSidebarButton.classList.toggle('toggle-sidebar-active', !sidebar.classList.contains('sidebar-hidden'));
    });

    clearSearchButton.addEventListener('click', () => {
        // Get the search results area by its class
        const searchResultsArea = document.querySelector('.search-results-area');

        // Reset the content of the search results area to empty, effectively clearing it
        searchResultsArea.innerHTML = '';
    });

    document.getElementById('complete-workflow').addEventListener('click', () => {
    
        // Reveal the sidebar by removing the 'sidebar-hidden' class or adjusting the style directly
        document.querySelector('.sidebar').classList.remove('sidebar-hidden');
    });

    document.querySelector('.workflow-list').addEventListener('click', (e) => {
        if (e.target && e.target.matches('.workflow-sub-item')) {
            e.stopPropagation();
            const previouslySelected = document.querySelector('.workflow-sub-item.selected');
            if (previouslySelected && previouslySelected !== e.target) {
                previouslySelected.classList.remove('selected');
                previouslySelected.style.backgroundColor = "";
            }
            const isSelected = e.target.classList.contains('selected');
            if (isSelected) {
                e.target.classList.remove('selected');
                e.target.style.backgroundColor = "";
                outputArea.textContent = "";
            } else {
                e.target.classList.add('selected');
                e.target.style.backgroundColor = "purple";
                const fileName = e.target.textContent;
                window.electronAPI.sendMessage('readFileContent', fileName);
            }
        }
        else if (e.target && e.target.classList.contains('workflow-item')) {
            const isSelected = !e.target.classList.contains('selected');
            clearSelections(isSelected ? e.target : null);
            e.target.classList.toggle('selected', isSelected);
            e.target.style.border = isSelected ? "2px solid blue" : "";
            toggleSubListVisibility(e.target, isSelected);
        }

        checkAndToggleCompleteButtonVisibility();
        checkAndToggleWorkflowButtonsVisibility();
    });

    document.getElementById('reset-workflow').addEventListener('click', () => {
        window.electronAPI.sendMessage('resetProcessedDataFiles');
        console.log('Reset workflow initiated.');
    });

    document.getElementById('workflow-output').addEventListener('click', () => {
        isFlowOutputShown = !isFlowOutputShown;

        if (isFlowOutputShown) {
            window.electronAPI.sendMessage('readWorkflowOutput');
        } else {
            document.querySelector('.output-area').textContent = '';
        }
    });

    document.getElementById('search-button').addEventListener('click', () => {
        const searchQuery = document.getElementById('search').value.trim();
        if (searchQuery) {
            // Trigger the search operation
            window.electronAPI.sendMessage('searchWorkflowContent', searchQuery);
    
            // Immediately show the clear search button, regardless of search results
            document.getElementById('clear-search').style.display = 'block';
    
            // Reveal the sidebar by removing the 'sidebar-hidden' class
            document.querySelector('.sidebar').classList.remove('sidebar-hidden');
            
            // Wait for a second (1000 milliseconds), then reset the text in the search input area
            setTimeout(() => {
                document.getElementById('search').value = '';
                // Since the input is now cleared, you might want to hide the search button again
                // if your UI logic requires the search button to only be visible when there's input
                toggleSearchButtonVisibility();
                // Consider updating the clear search button visibility as needed
                toggleClearSearchButtonVisibility();
            }, 100); // Adjusted the timeout to 1000 milliseconds for the actual wait
        }
    });
    
    window.electronAPI.sendMessage('getProcessedDataFiles');

    window.electronAPI.receiveMessage('processedDataFilesResponse', (files) => {
        updateSublist(files);

        checkAndToggleCompleteButtonVisibility();
        checkAndToggleWorkflowButtonsVisibility();
    });

    window.electronAPI.receiveMessage('fileContentResponse', (content) => {
        const outputArea = document.querySelector('.output-area');
        outputArea.textContent = content;
    });

    window.electronAPI.receiveMessage('csharp-output', (output) => {
        const outputArea = document.querySelector('.output-area');
        outputArea.textContent += output + '\n';
    });

    window.electronAPI.receiveMessage('csharp-error', (error) => {
        const outputArea = document.querySelector('.output-area');
        outputArea.textContent += 'Error: ' + error + '\n';
    });

    window.electronAPI.receiveMessage('updateOutputArea', (data) => {
        const outputArea = document.querySelector('.output-area');
        outputArea.textContent = data;
    });

    window.electronAPI.receiveMessage('searchResults', (data) => {
        const resultsArea = document.querySelector('.search-results-area');
        resultsArea.innerHTML = ''; // Clear previous results

        // Check if the directory was not found
        if (data.directoryNotFound) {
            resultsArea.textContent = "The workflow directory was not found.";
            return; // Exit early as there's nothing more to do
        }

        // If no results but directories were searched
        if (!data.results || data.results.length === 0) {
            let searchedPathsFormatted = data.searchedPaths.map(path =>
                path.replace(/\\/g, ' > ')
            ).join('<br>');

            let message = `Searched paths:<br><br>${searchedPathsFormatted}<br><br>Search pattern "${data.searchQuery}" not found in any file.`;
            resultsArea.innerHTML = message; // Use innerHTML to allow HTML formatting
            return; // Exit after handling no results found
        }

        // Handle and display search results
        data.results.forEach(result => {
            if (result && result.path && result.line) {
                const pathFormatted = result.path.replace(/\\/g, ' > ');
                const patternRegex = new RegExp(`(${data.searchQuery})`, 'ig');
                const highlightedLine = result.line.replace(patternRegex, `<span class="highlight">$1</span>`);

                const resultElement = document.createElement('div');
                resultElement.innerHTML = `<p>Found in path:</p><br><p>${pathFormatted}</p><br><p>${highlightedLine}</p>`;
                resultsArea.appendChild(resultElement);
            } else {
                console.warn('A result is missing expected properties:', result);
            }
        });

        toggleClearSearchButtonVisibility();
    });

    document.getElementById('clear-search').addEventListener('click', () => {
        const searchResultsArea = document.querySelector('.search-results-area');
    
        // Clear the content of the search results area
        searchResultsArea.innerHTML = '';
    
        // Hide the clear search button since the search results have been cleared
        document.getElementById('clear-search').style.display = 'none';
    
        // Optionally, clear the search input field as well
        //document.getElementById('search').value = '';
        // Update the visibility of the search button based on the now empty search input
        toggleSearchButtonVisibility();
    });
});
