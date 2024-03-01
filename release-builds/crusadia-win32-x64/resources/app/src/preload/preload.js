const { contextBridge, ipcRenderer } = require('electron');

const validSendChannels = [
    'getProcessedDataFiles',
    'readFileContent',
    'openApplication',
    'resetProcessedDataFiles',
    'readWorkflowOutput',
    'readResetLog',
    'searchWorkflowContent'
];

const validReceiveChannels = [
    'processedDataFilesResponse',
    'fileContentResponse',
    'csharp-output',
    'csharp-error',
    'updateOutputArea',
    'searchResults'
];

contextBridge.exposeInMainWorld('electronAPI', {
    sendMessage: (channel, data) => {
        if (validSendChannels.includes(channel)) {
            ipcRenderer.send(channel, data);
        } else {
            console.error(`Attempted to send message on invalid channel: ${channel}`);
        }
    },
    receiveMessage: (channel, func) => {
        if (validReceiveChannels.includes(channel)) {
            ipcRenderer.removeAllListeners(channel);
            ipcRenderer.on(channel, (event, ...args) => func(...args));
        } else {
            console.error(`Attempted to receive message on invalid channel: ${channel}`);
        }
    },
});
