#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

struct Worker {
  Worker(int index, long long finishTime) : index(index), finishTime(finishTime) {}
  int index;
  long long finishTime;

  bool operator<(Worker a) {
    return finishTime < a.finishTime || (finishTime == a.finishTime && index < a.index);
  }
};

class WorkerMinHeap {
  public: 

  WorkerMinHeap(int numWorkers){
    n = numWorkers;
    for (int i = 0; i < n;++i){
      data_.push_back(Worker(i, 0));
    }
  }
  Worker Min(){
    return data_[0];
  }

  void ChangePriority(int i, long long newPriorityFinishTime) {
    long long oldFinishTime = data_[i].finishTime;
    data_[i].finishTime = newPriorityFinishTime;

    if(newPriorityFinishTime < oldFinishTime){
      SiftUp(i);
    }
    else {
      SiftDown(i);
    }

    SiftDown(i);
  }

private:
  vector<Worker> data_;
  int n;

  int Parent(int i) {
    return (i - 1) / 2;
  }

  int Left(int i){
    return i * 2 + 1;
  }

  int Right(int i){
    return i * 2 + 2;
  }

  void Heapify() {
    for (int i = data_.size() / 2; i >= 0; --i){
      SiftDown(i);
    }
  }

  void SiftDown(int i) {
    int minIndex = i;
    int j1 = Left(i);
    int j2 = Right(i);    
    
    if(j1 < data_.size() && data_[j1] < data_[minIndex])
      minIndex = j1;

    if (j2 < data_.size() && data_[j2] < data_[minIndex])
      minIndex = j2;

    if(i != minIndex) {      
      std::swap(data_[i], data_[minIndex]);
      SiftDown(minIndex);
    }
  }

  void SiftUp(int i){
    while (i > 0 && data_[i] < data_[Parent(i)]){
      std::swap(data_[i], data_[Parent(i)]);
      i = Parent(i);
    }
  }
};

class JobQueue
{
private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());

    WorkerMinHeap workers = WorkerMinHeap(num_workers_);

    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      Worker next_worker = workers.Min();

      assigned_workers_[i] = next_worker.index;
      start_times_[i] = next_worker.finishTime;

      workers.ChangePriority(0, next_worker.finishTime + duration);
    }
  }


 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
