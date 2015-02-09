using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Config_UI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            List<Device> devs = new List<Device>();
            devs.Add(new Device() { Name = "Device 1", Status = "Redy", IPAddress = "1.1.1.1" });
            devs.Add(new Device() { Name = "Device 2", Status = "Redy", IPAddress = "1.1.1.2" });
            devs.Add(new Device() { Name = "Device 3", Status = "Failed", IPAddress = "1.1.1.3" });
            devs.Add(new Device() { Name = "Device 4", Status = "Unknown", IPAddress = "1.1.1.4" });
            gridDevices.ItemsSource = devs;
        }

        private void CommandBinding_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void CommandBinding_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            mainWindow.Close();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            MessageBoxResult messageBoxResult = System.Windows.MessageBox.Show("Are you sure?", "Exit Confirmation", System.Windows.MessageBoxButton.YesNo);
            if (messageBoxResult == MessageBoxResult.Yes)
            {
                Application.Current.Shutdown();
            }
            else
            {
                e.Cancel = true;
            }
        }
    }

    public class Device
    {
        public string Name { get; set; }
        public string Status { get; set; }
        public string IPAddress { get; set; }
    }
}
