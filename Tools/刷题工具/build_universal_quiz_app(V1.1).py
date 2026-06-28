import importlib.util
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
OUT_PATH = ROOT / "outputs" / "通用刷题工具.html"
OLD_BUILDER = ROOT / "work" / "build_xigai_quiz_app.py"


def load_default_questions():
    spec = importlib.util.spec_from_file_location("xigai_builder", OLD_BUILDER)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.build_questions()


HTML = r'''<!doctype html>
<html lang="zh-CN">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>通用刷题工具</title>
  <style>
    :root {
      --bg: #f6f7f3;
      --panel: #ffffff;
      --ink: #17201a;
      --muted: #69736a;
      --line: #dfe4dc;
      --accent: #176b4a;
      --accent-2: #e7f2ec;
      --bad: #b83232;
      --bad-bg: #fae8e8;
      --good: #167343;
      --good-bg: #e6f3ea;
      --warn: #946200;
      --warn-bg: #fff3cf;
      --radius: 10px;
    }
    * { box-sizing: border-box; }
    body {
      margin: 0;
      min-height: 100dvh;
      color: var(--ink);
      background: var(--bg);
      font-family: "Microsoft YaHei", "PingFang SC", system-ui, sans-serif;
    }
    button, input, select, textarea { font: inherit; }
    button {
      border: 1px solid var(--line);
      background: var(--panel);
      color: var(--ink);
      border-radius: var(--radius);
      padding: 10px 14px;
      cursor: pointer;
      transition: transform .12s ease, border-color .12s ease, background .12s ease;
    }
    button:hover { border-color: #b9c7bc; }
    button:active { transform: translateY(1px); }
    button.primary {
      border-color: var(--accent);
      background: var(--accent);
      color: #fff;
      font-weight: 700;
    }
    button.danger {
      color: var(--bad);
      border-color: #efb8b8;
      background: #fff7f7;
    }
    select, input, textarea {
      width: 100%;
      max-width: 100%;
      min-width: 0;
      border: 1px solid var(--line);
      background: var(--panel);
      color: var(--ink);
      border-radius: var(--radius);
      padding: 9px 10px;
      outline: none;
    }
    select, input { min-height: 42px; }
    textarea {
      min-height: 190px;
      resize: vertical;
      line-height: 1.6;
    }
    select:focus, input:focus, textarea:focus {
      border-color: var(--accent);
      box-shadow: 0 0 0 3px rgb(23 107 74 / .14);
    }
    .app {
      width: min(1180px, calc(100% - 28px));
      margin: 0 auto;
      padding: 22px 0 36px;
    }
    .topbar {
      display: grid;
      grid-template-columns: 1fr auto;
      gap: 16px;
      align-items: end;
      padding-bottom: 16px;
      border-bottom: 1px solid var(--line);
    }
    h1 {
      margin: 0 0 6px;
      font-size: clamp(24px, 3vw, 38px);
      line-height: 1.1;
      letter-spacing: 0;
    }
    .subtitle {
      margin: 0;
      color: var(--muted);
      line-height: 1.6;
    }
    .stats {
      display: grid;
      grid-template-columns: repeat(4, minmax(86px, 1fr));
      gap: 8px;
      min-width: 410px;
    }
    .stat {
      border: 1px solid var(--line);
      background: var(--panel);
      border-radius: var(--radius);
      padding: 10px;
    }
    .stat b {
      display: block;
      font-size: 22px;
      line-height: 1;
    }
    .stat span {
      display: block;
      margin-top: 6px;
      color: var(--muted);
      font-size: 12px;
    }
    .layout {
      display: grid;
      grid-template-columns: minmax(240px, 280px) minmax(0, 1fr);
      gap: 16px;
      margin-top: 16px;
    }
    .sidebar, .main, .review-panel, .import-panel {
      border: 1px solid var(--line);
      background: var(--panel);
      border-radius: var(--radius);
    }
    .sidebar {
      padding: 14px;
      align-self: start;
      position: sticky;
      top: 12px;
    }
    .control {
      display: grid;
      min-width: 0;
      gap: 7px;
      margin-bottom: 12px;
    }
    .control label {
      color: var(--muted);
      font-size: 13px;
    }
    .seg {
      display: grid;
      grid-template-columns: repeat(2, 1fr);
      gap: 6px;
    }
    .seg button.active {
      border-color: var(--accent);
      background: var(--accent-2);
      color: var(--accent);
      font-weight: 700;
    }
    .side-actions {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 8px;
      margin-top: 14px;
    }
    .tip {
      margin-top: 14px;
      color: var(--muted);
      font-size: 13px;
      line-height: 1.65;
      border-top: 1px solid var(--line);
      padding-top: 12px;
    }
    .main {
      min-width: 0;
      min-height: 560px;
      padding: 20px;
    }
    .question-head {
      display: flex;
      justify-content: space-between;
      align-items: flex-start;
      gap: 12px;
      padding-bottom: 14px;
      border-bottom: 1px solid var(--line);
    }
    .badges {
      display: flex;
      flex-wrap: wrap;
      gap: 8px;
      align-items: center;
    }
    .badge {
      display: inline-flex;
      align-items: center;
      min-height: 28px;
      border: 1px solid var(--line);
      border-radius: 999px;
      padding: 4px 10px;
      color: var(--muted);
      background: #fbfcfa;
      font-size: 13px;
    }
    .badge.strong {
      color: var(--accent);
      border-color: #b8d2c4;
      background: var(--accent-2);
      font-weight: 700;
    }
    .star {
      min-width: 44px;
      min-height: 42px;
      padding: 8px 10px;
      color: var(--warn);
      background: var(--warn-bg);
      border-color: #ead18d;
    }
    .question {
      margin: 20px 0;
      font-size: clamp(19px, 2vw, 25px);
      line-height: 1.65;
      font-weight: 700;
      white-space: pre-wrap;
    }
    .options {
      display: grid;
      gap: 10px;
    }
    .option {
      display: grid;
      grid-template-columns: 42px 1fr;
      gap: 10px;
      align-items: center;
      border: 1px solid var(--line);
      border-radius: var(--radius);
      background: #fff;
      padding: 12px;
      text-align: left;
      width: 100%;
    }
    .option .key {
      display: grid;
      place-items: center;
      height: 34px;
      border-radius: 8px;
      background: #eef1ec;
      font-weight: 800;
      color: #425044;
    }
    .option.selected { border-color: var(--accent); background: #f1f8f4; }
    .option.correct { border-color: #8ec5a5; background: var(--good-bg); }
    .option.wrong { border-color: #e3a4a4; background: var(--bad-bg); }
    .option.correct .key { background: var(--good); color: #fff; }
    .option.wrong .key { background: var(--bad); color: #fff; }
    .answer-box {
      display: none;
      margin-top: 16px;
      padding: 14px;
      border-radius: var(--radius);
      border: 1px solid var(--line);
      line-height: 1.7;
    }
    .answer-box.show { display: block; }
    .answer-box.good { background: var(--good-bg); border-color: #97caaa; }
    .answer-box.bad { background: var(--bad-bg); border-color: #e3a4a4; }
    .actions {
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
      align-items: center;
      margin-top: 18px;
    }
    .review-panel, .import-panel {
      margin-top: 16px;
      padding: 16px;
      display: none;
    }
    .review-panel.show, .import-panel.show { display: block; }
    .review-list {
      display: grid;
      gap: 8px;
      margin-top: 12px;
      max-height: 360px;
      overflow: auto;
    }
    .review-item {
      border: 1px solid var(--line);
      border-radius: var(--radius);
      padding: 10px;
      background: #fff;
      cursor: pointer;
      line-height: 1.5;
    }
    .review-item:hover { border-color: var(--accent); }
    .empty {
      display: grid;
      place-items: center;
      min-height: 360px;
      color: var(--muted);
      text-align: center;
      line-height: 1.7;
    }
    .progress {
      height: 8px;
      border-radius: 999px;
      background: #e6ebe5;
      overflow: hidden;
      margin-top: 12px;
    }
    .progress span {
      display: block;
      height: 100%;
      width: 0%;
      background: var(--accent);
    }
    .import-grid {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 14px;
      margin-top: 12px;
    }
    .format-help {
      color: var(--muted);
      font-size: 13px;
      line-height: 1.65;
      border: 1px dashed #c8d2c8;
      background: #fbfcfa;
      border-radius: var(--radius);
      padding: 12px;
      white-space: pre-wrap;
    }
    .import-actions {
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
      margin-top: 12px;
      align-items: center;
    }
    .toast {
      position: fixed;
      left: 50%;
      bottom: 18px;
      transform: translateX(-50%);
      background: #17201a;
      color: #fff;
      padding: 10px 14px;
      border-radius: 999px;
      opacity: 0;
      pointer-events: none;
      transition: opacity .18s ease, transform .18s ease;
      z-index: 20;
    }
    .toast.show {
      opacity: 1;
      transform: translateX(-50%) translateY(-4px);
    }
    @media (max-width: 1100px) {
      .app { width: min(100% - 20px, 1180px); }
      .layout { grid-template-columns: minmax(210px, 250px) minmax(0, 1fr); gap: 12px; }
      .sidebar { padding: 12px; }
      select, input { font-size: 15px; }
    }
    @media (max-width: 860px) {
      .topbar, .layout, .import-grid { grid-template-columns: 1fr; }
      .stats { min-width: 0; grid-template-columns: repeat(2, 1fr); }
      .sidebar { position: static; }
      .main { padding: 16px; }
      .question-head { flex-direction: column; }
    }
  </style>
</head>
<body>
  <div class="app">
    <header class="topbar">
      <div>
        <h1 id="appTitle">通用刷题工具</h1>
        <p class="subtitle" id="subtitle">可直接刷内置习概题库，也可以导入 docx、txt、markdown 或 JSON 题库。</p>
      </div>
      <div class="stats">
        <div class="stat"><b id="totalCount">0</b><span>题库总量</span></div>
        <div class="stat"><b id="doneCount">0</b><span>已答题次</span></div>
        <div class="stat"><b id="accuracy">0%</b><span>正确率</span></div>
        <div class="stat"><b id="wrongCount">0</b><span>错题数</span></div>
      </div>
    </header>

    <section class="layout">
      <aside class="sidebar">
        <div class="control">
          <label for="typeFilter">题型</label>
          <select id="typeFilter">
            <option value="all">全部题型</option>
            <option value="single">单选题</option>
            <option value="multi">多选题</option>
            <option value="judge">判断题</option>
          </select>
        </div>
        <div class="control">
          <label for="chapterFilter">章节</label>
          <select id="chapterFilter"></select>
        </div>
        <div class="control">
          <label for="searchInput">搜索题干/选项</label>
          <input id="searchInput" type="search" placeholder="例如：共同富裕" />
        </div>
        <div class="control">
          <label>练习范围</label>
          <div class="seg">
            <button id="modeAll" class="active" type="button">全部</button>
            <button id="modeWrong" type="button">错题</button>
            <button id="modeFav" type="button">收藏</button>
            <button id="modeUnseen" type="button">未做</button>
          </div>
        </div>
        <div class="side-actions">
          <button id="randomBtn" class="primary" type="button">随机抽题</button>
          <button id="reviewBtn" type="button">题目列表</button>
          <button id="importBtn" type="button">导入题库</button>
          <button id="exportBtn" type="button">导出JSON</button>
          <button id="defaultBtn" type="button">内置题库</button>
          <button id="resetAllBtn" class="danger" type="button">清空记录</button>
        </div>
        <div class="progress"><span id="progressBar"></span></div>
        <div class="tip">
          快捷键：A/B/C/D/E/F 选择，Enter 提交，N 下一题，S 收藏。导入 docx 时会在浏览器本地读取，不上传文件。
        </div>
      </aside>

      <main>
        <section class="main" id="mainPanel">
          <div id="emptyState" class="empty">正在载入题库...</div>
          <div id="quizArea" style="display:none">
            <div class="question-head">
              <div class="badges">
                <span class="badge strong" id="typeBadge">题型</span>
                <span class="badge" id="chapterBadge">章节</span>
                <span class="badge" id="numberBadge">编号</span>
              </div>
              <button id="favBtn" class="star" type="button">☆</button>
            </div>
            <div class="question" id="questionText"></div>
            <div class="options" id="options"></div>
            <div id="answerBox" class="answer-box"></div>
            <div class="actions">
              <button id="submitBtn" class="primary" type="button">提交答案</button>
              <button id="showAnswerBtn" type="button">直接看答案</button>
              <button id="nextBtn" type="button">下一题</button>
            </div>
          </div>
        </section>

        <section class="import-panel" id="importPanel">
          <strong>导入题库</strong>
          <div class="import-grid">
            <div>
              <div class="control" style="margin-top:12px">
                <label for="fileInput">选择文件（.docx / .txt / .md / .json）</label>
                <input id="fileInput" type="file" accept=".docx,.txt,.md,.markdown,.json,application/vnd.openxmlformats-officedocument.wordprocessingml.document,application/json,text/plain,text/markdown" />
              </div>
              <div class="control">
                <label for="pasteInput">或粘贴题库文本</label>
                <textarea id="pasteInput" placeholder="把题库文本粘贴到这里，然后点击“解析导入”。"></textarea>
              </div>
              <div class="import-actions">
                <button id="parseImportBtn" class="primary" type="button">解析导入</button>
                <button id="clearImportBtn" type="button">清空文本</button>
              </div>
              <p class="subtitle" id="importStatus" style="margin-top:10px"></p>
            </div>
            <div class="format-help">推荐格式：

# 第一章 绪论

## 单选题
1. 实现（ ）是近代以来中国人民的共同梦想。
A. 国家富强
B. 中华民族伟大复兴
C. 人民幸福
D. 民族振兴
答案：B

## 多选题
1. 以下属于背景的是（ ）。
A. 世界百年未有之大变局
B. 民族复兴进入关键时期
C. 经济高速发展
D. 世界领导角色
答案：AB

## 判断题
1. 自我革命是第一个答案。
答案：错

也支持答案写在题干里，例如：1. 中国特色社会主义最本质的特征是（C）。</div>
          </div>
        </section>

        <section class="review-panel" id="reviewPanel">
          <strong id="reviewTitle">题目列表</strong>
          <div class="review-list" id="reviewList"></div>
        </section>
      </main>
    </section>
  </div>
  <div id="toast" class="toast"></div>

  <script id="question-data" type="application/json">__QUESTIONS__</script>
  <script>
    const defaultQuestions = JSON.parse(document.getElementById('question-data').textContent);
    let questions = defaultQuestions;
    let bankName = '内置习概题库';
    const typeNames = { single: '单选题', multi: '多选题', judge: '判断题' };
    let storeKey = makeStoreKey(bankName);
    const state = {
      current: null,
      selected: new Set(),
      answered: false,
      mode: 'all',
      progress: loadProgress(),
    };

    const $ = (id) => document.getElementById(id);
    const els = {
      appTitle: $('appTitle'),
      subtitle: $('subtitle'),
      totalCount: $('totalCount'),
      doneCount: $('doneCount'),
      accuracy: $('accuracy'),
      wrongCount: $('wrongCount'),
      typeFilter: $('typeFilter'),
      chapterFilter: $('chapterFilter'),
      searchInput: $('searchInput'),
      modeAll: $('modeAll'),
      modeWrong: $('modeWrong'),
      modeFav: $('modeFav'),
      modeUnseen: $('modeUnseen'),
      randomBtn: $('randomBtn'),
      reviewBtn: $('reviewBtn'),
      importBtn: $('importBtn'),
      exportBtn: $('exportBtn'),
      defaultBtn: $('defaultBtn'),
      resetAllBtn: $('resetAllBtn'),
      progressBar: $('progressBar'),
      emptyState: $('emptyState'),
      quizArea: $('quizArea'),
      typeBadge: $('typeBadge'),
      chapterBadge: $('chapterBadge'),
      numberBadge: $('numberBadge'),
      favBtn: $('favBtn'),
      questionText: $('questionText'),
      options: $('options'),
      answerBox: $('answerBox'),
      submitBtn: $('submitBtn'),
      showAnswerBtn: $('showAnswerBtn'),
      nextBtn: $('nextBtn'),
      importPanel: $('importPanel'),
      fileInput: $('fileInput'),
      pasteInput: $('pasteInput'),
      parseImportBtn: $('parseImportBtn'),
      clearImportBtn: $('clearImportBtn'),
      importStatus: $('importStatus'),
      reviewPanel: $('reviewPanel'),
      reviewTitle: $('reviewTitle'),
      reviewList: $('reviewList'),
      toast: $('toast'),
    };

    function makeStoreKey(name) {
      return 'universal_quiz_progress_v2_' + String(name || 'bank').slice(0, 80);
    }

    function loadProgress() {
      try { return JSON.parse(localStorage.getItem(storeKey)) || {}; }
      catch { return {}; }
    }

    function saveProgress() {
      localStorage.setItem(storeKey, JSON.stringify(state.progress));
    }

    function recordFor(id) {
      if (!state.progress[id]) state.progress[id] = { seen: 0, right: 0, wrong: 0, fav: false, last: 0 };
      return state.progress[id];
    }

    function normalizeAnswer(answer) {
      return String(answer || '').toUpperCase().replace(/[，,\s、]/g, '').split('').sort().join('');
    }

    function getFilters() {
      return {
        type: els.typeFilter.value,
        chapter: els.chapterFilter.value,
        keyword: els.searchInput.value.trim().toLowerCase(),
      };
    }

    function questionMatches(q) {
      const f = getFilters();
      if (f.type !== 'all' && q.type !== f.type) return false;
      if (f.chapter !== 'all' && q.chapter !== f.chapter) return false;
      if (f.keyword) {
        const hay = [q.question, q.chapter, ...q.options.map(o => o.text), q.explanation || ''].join(' ').toLowerCase();
        if (!hay.includes(f.keyword)) return false;
      }
      const rec = state.progress[q.id];
      if (state.mode === 'wrong' && (!rec || rec.wrong <= 0)) return false;
      if (state.mode === 'fav' && (!rec || !rec.fav)) return false;
      if (state.mode === 'unseen' && rec && rec.seen > 0) return false;
      return true;
    }

    function filteredQuestions() {
      return questions.filter(questionMatches);
    }

    function pickRandom() {
      const pool = filteredQuestions();
      if (!pool.length) {
        state.current = null;
        renderEmpty('当前筛选条件下没有题目。可以切回“全部”，或者换一个章节。');
        renderReview();
        return;
      }
      state.current = pool[Math.floor(Math.random() * pool.length)];
      state.selected = new Set();
      state.answered = false;
      renderQuestion();
      renderReview();
    }

    function renderQuestion() {
      const q = state.current;
      els.emptyState.style.display = 'none';
      els.quizArea.style.display = 'block';
      els.typeBadge.textContent = typeNames[q.type] || q.type;
      els.chapterBadge.textContent = q.chapter || '未分章';
      els.numberBadge.textContent = `第 ${q.number || ''} 题`;
      els.questionText.textContent = q.question;
      const rec = state.progress[q.id];
      els.favBtn.textContent = rec && rec.fav ? '★' : '☆';
      els.options.innerHTML = '';
      q.options.forEach((opt) => {
        const btn = document.createElement('button');
        btn.type = 'button';
        btn.className = 'option';
        btn.dataset.key = opt.key;
        btn.innerHTML = `<span class="key">${escapeHtml(opt.key)}</span><span>${escapeHtml(opt.text)}</span>`;
        btn.addEventListener('click', () => toggleOption(opt.key));
        els.options.appendChild(btn);
      });
      els.answerBox.className = 'answer-box';
      els.answerBox.textContent = '';
      renderSelected();
      updateStats();
    }

    function renderEmpty(message) {
      els.quizArea.style.display = 'none';
      els.emptyState.style.display = 'grid';
      els.emptyState.textContent = message;
      updateStats();
    }

    function toggleOption(key) {
      if (!state.current || state.answered) return;
      if (state.current.type === 'multi') {
        if (state.selected.has(key)) state.selected.delete(key);
        else state.selected.add(key);
      } else {
        state.selected = new Set([key]);
      }
      renderSelected();
    }

    function renderSelected() {
      [...els.options.querySelectorAll('.option')].forEach((btn) => {
        btn.classList.toggle('selected', state.selected.has(btn.dataset.key));
      });
    }

    function submitAnswer(forceShow = false) {
      const q = state.current;
      if (!q || state.answered) return;
      if (!forceShow && state.selected.size === 0) {
        showToast('先选一个答案');
        return;
      }
      const picked = normalizeAnswer([...state.selected].join(''));
      const correct = picked === q.answer;
      state.answered = true;
      if (!forceShow) {
        const rec = recordFor(q.id);
        rec.seen += 1;
        rec.last = Date.now();
        if (correct) rec.right += 1;
        else rec.wrong += 1;
        if (correct && rec.wrong > 0) rec.wrong -= 1;
        saveProgress();
      }
      [...els.options.querySelectorAll('.option')].forEach((btn) => {
        const key = btn.dataset.key;
        if (q.answer.includes(key)) btn.classList.add('correct');
        if (!q.answer.includes(key) && state.selected.has(key)) btn.classList.add('wrong');
      });
      els.answerBox.className = `answer-box show ${correct || forceShow ? 'good' : 'bad'}`;
      const answerText = q.answer === 'T' ? '正确' : q.answer === 'F' ? '错误' : q.answer;
      const explanation = q.explanation ? `<br>解析：${escapeHtml(q.explanation)}` : '';
      els.answerBox.innerHTML = `${forceShow ? '答案' : (correct ? '答对了' : '答错了')}：<strong>${answerText}</strong>${explanation}`;
      updateStats();
      renderReview();
    }

    function toggleFavorite() {
      if (!state.current) return;
      const rec = recordFor(state.current.id);
      rec.fav = !rec.fav;
      saveProgress();
      els.favBtn.textContent = rec.fav ? '★' : '☆';
      updateStats();
      renderReview();
      showToast(rec.fav ? '已收藏' : '已取消收藏');
    }

    function setMode(mode) {
      state.mode = mode;
      [els.modeAll, els.modeWrong, els.modeFav, els.modeUnseen].forEach(b => b.classList.remove('active'));
      ({ all: els.modeAll, wrong: els.modeWrong, fav: els.modeFav, unseen: els.modeUnseen })[mode].classList.add('active');
      pickRandom();
    }

    function updateStats() {
      const values = Object.values(state.progress);
      const answeredIds = values.filter(r => r.seen > 0).length;
      const wrongIds = values.filter(r => r.wrong > 0).length;
      const totalSeen = values.reduce((sum, r) => sum + (r.seen || 0), 0);
      const totalRight = values.reduce((sum, r) => sum + (r.right || 0), 0);
      els.totalCount.textContent = questions.length;
      els.doneCount.textContent = totalSeen;
      els.accuracy.textContent = totalSeen ? Math.round(totalRight / totalSeen * 100) + '%' : '0%';
      els.wrongCount.textContent = wrongIds;
      els.progressBar.style.width = questions.length ? Math.round(answeredIds / questions.length * 100) + '%' : '0%';
    }

    function renderReview() {
      const pool = filteredQuestions();
      els.reviewTitle.textContent = `题目列表：${pool.length} 道`;
      els.reviewList.innerHTML = '';
      pool.slice(0, 220).forEach((q) => {
        const rec = state.progress[q.id];
        const item = document.createElement('div');
        item.className = 'review-item';
        const mark = rec && rec.wrong > 0 ? '错题' : rec && rec.seen > 0 ? '已做' : '未做';
        item.innerHTML = `<strong>${escapeHtml(typeNames[q.type] || q.type)} ${q.number || ''}</strong> <span style="color:#69736a">${escapeHtml(q.chapter || '未分章')} · ${mark}</span><br>${escapeHtml(q.question.slice(0, 110))}`;
        item.addEventListener('click', () => {
          state.current = q;
          state.selected = new Set();
          state.answered = false;
          renderQuestion();
          window.scrollTo({ top: 0, behavior: 'smooth' });
        });
        els.reviewList.appendChild(item);
      });
      if (pool.length > 220) {
        const note = document.createElement('div');
        note.className = 'review-item';
        note.textContent = '只显示前 220 道。可以用章节、题型或搜索缩小范围。';
        els.reviewList.appendChild(note);
      }
    }

    function populateChapters() {
      const chapters = [...new Set(questions.map(q => q.chapter || '未分章'))];
      els.chapterFilter.innerHTML = '<option value="all">全部章节</option>' + chapters.map(ch => `<option value="${escapeAttr(ch)}">${escapeHtml(ch)}</option>`).join('');
    }

    function switchQuestionBank(nextQuestions, nextName) {
      const normalized = nextQuestions === defaultQuestions ? defaultQuestions : normalizeImportedQuestions(nextQuestions, nextName);
      if (!normalized.length) throw new Error('没有识别到题目');
      questions = normalized;
      bankName = nextName || '导入题库';
      storeKey = makeStoreKey(bankName);
      state.progress = loadProgress();
      state.current = null;
      state.selected = new Set();
      state.answered = false;
      els.appTitle.textContent = bankName;
      els.subtitle.textContent = `当前题库：${bankName}。共 ${questions.length} 道题。`;
      populateChapters();
      updateStats();
      pickRandom();
      renderReview();
    }

    function normalizeImportedQuestions(raw, name) {
      const list = Array.isArray(raw) ? raw : (raw && Array.isArray(raw.questions) ? raw.questions : []);
      return list.map((q, idx) => {
        const type = normalizeType(q.type, q.answer, q.options);
        const options = normalizeOptions(q.options, type);
        return {
          id: `${name || 'bank'}-${type}-${idx + 1}`,
          type,
          number: q.number || idx + 1,
          chapter: q.chapter || '未分章',
          question: String(q.question || q.title || '').trim(),
          options,
          answer: normalizeImportedAnswer(q.answer, type),
          explanation: q.explanation || q.analysis || '',
        };
      }).filter(q => q.question && q.options.length && q.answer);
    }

    function normalizeType(type, answer, options) {
      const t = String(type || '').toLowerCase();
      if (['single', 'multi', 'judge'].includes(t)) return t;
      if (/判断|true|false|tf/.test(t)) return 'judge';
      const ans = normalizeImportedAnswer(answer, '');
      if (ans === 'T' || ans === 'F') return 'judge';
      if (ans.length > 1) return 'multi';
      return 'single';
    }

    function normalizeOptions(options, type) {
      if (type === 'judge') return [{ key: 'T', text: '正确' }, { key: 'F', text: '错误' }];
      if (Array.isArray(options)) {
        return options.map((o, i) => {
          if (typeof o === 'string') return { key: String.fromCharCode(65 + i), text: o.trim() };
          return { key: String(o.key || String.fromCharCode(65 + i)).toUpperCase(), text: String(o.text || o.value || '').trim() };
        }).filter(o => o.text);
      }
      return [];
    }

    function normalizeImportedAnswer(answer, type) {
      let raw = String(answer || '').trim().toUpperCase();
      raw = raw.replace(/[答案：:]/g, '').replace(/[，,\s、]/g, '');
      if (/^(正确|对|TRUE|T|√|✓)$/.test(raw)) return 'T';
      if (/^(错误|错|FALSE|F|×|X)$/.test(raw)) return 'F';
      return raw.replace(/[^A-F]/g, '').split('').sort().join('');
    }

    async function readSelectedFile() {
      const file = els.fileInput.files && els.fileInput.files[0];
      if (!file) return null;
      const lower = file.name.toLowerCase();
      if (lower.endsWith('.json')) {
        return { name: file.name.replace(/\.[^.]+$/, ''), text: await file.text(), kind: 'json' };
      }
      if (lower.endsWith('.docx')) {
        return { name: file.name.replace(/\.[^.]+$/, ''), text: await extractDocxText(file), kind: 'text' };
      }
      return { name: file.name.replace(/\.[^.]+$/, ''), text: await file.text(), kind: 'text' };
    }

    async function extractDocxText(file) {
      const bytes = new Uint8Array(await file.arrayBuffer());
      const xmlBytes = await readZipEntry(bytes, 'word/document.xml');
      const xml = new TextDecoder('utf-8').decode(xmlBytes);
      const doc = new DOMParser().parseFromString(xml, 'application/xml');
      const paragraphs = [...doc.getElementsByTagName('w:p')].map(p => {
        const chunks = [...p.getElementsByTagName('w:t')].map(t => t.textContent || '');
        return chunks.join('');
      }).map(s => s.trim()).filter(Boolean);
      return paragraphs.join('\n');
    }

    async function readZipEntry(bytes, wantedName) {
      const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
      let eocd = -1;
      for (let i = bytes.length - 22; i >= Math.max(0, bytes.length - 66000); i--) {
        if (view.getUint32(i, true) === 0x06054b50) { eocd = i; break; }
      }
      if (eocd < 0) throw new Error('不是有效的 docx/zip 文件');
      const cdSize = view.getUint32(eocd + 12, true);
      const cdOffset = view.getUint32(eocd + 16, true);
      let pos = cdOffset;
      const decoder = new TextDecoder('utf-8');
      while (pos < cdOffset + cdSize) {
        if (view.getUint32(pos, true) !== 0x02014b50) break;
        const method = view.getUint16(pos + 10, true);
        const compressedSize = view.getUint32(pos + 20, true);
        const nameLen = view.getUint16(pos + 28, true);
        const extraLen = view.getUint16(pos + 30, true);
        const commentLen = view.getUint16(pos + 32, true);
        const localOffset = view.getUint32(pos + 42, true);
        const name = decoder.decode(bytes.slice(pos + 46, pos + 46 + nameLen));
        if (name === wantedName) {
          const localNameLen = view.getUint16(localOffset + 26, true);
          const localExtraLen = view.getUint16(localOffset + 28, true);
          const dataStart = localOffset + 30 + localNameLen + localExtraLen;
          const compressed = bytes.slice(dataStart, dataStart + compressedSize);
          if (method === 0) return compressed;
          if (method === 8) return await inflateRaw(compressed);
          throw new Error('不支持的 docx 压缩方式');
        }
        pos += 46 + nameLen + extraLen + commentLen;
      }
      throw new Error('docx 中没有找到 word/document.xml');
    }

    async function inflateRaw(bytes) {
      if (!('DecompressionStream' in window)) {
        throw new Error('当前浏览器不支持本地解压 docx，请换 Chrome/Edge 或粘贴文本导入');
      }
      const stream = new Blob([bytes]).stream().pipeThrough(new DecompressionStream('deflate-raw'));
      return new Uint8Array(await new Response(stream).arrayBuffer());
    }

    function parseTextQuestions(text, name) {
      const normalized = text.replace(/\r/g, '\n').replace(/\u3000/g, ' ');
      const lines = normalized.split('\n').map(s => s.trim()).filter(Boolean);
      const starts = [];
      for (let i = 0; i < lines.length; i++) {
        if (/^\d{1,4}[.．、)\s]+/.test(lines[i])) starts.push(i);
      }
      const blocks = [];
      for (let i = 0; i < starts.length; i++) {
        blocks.push(lines.slice(starts[i], i + 1 < starts.length ? starts[i + 1] : lines.length).join('\n'));
      }
      let chapter = '未分章';
      let currentType = '';
      const parsed = [];
      const allBlocks = [];
      let buffer = [];
      for (const line of lines) {
        if (/^(#|\u300a)|第.+章|导论|绪论/.test(line) && !/^\d{1,4}/.test(line)) {
          chapter = cleanHeading(line);
        }
        if (/单选|单项选择/.test(line)) currentType = 'single';
        if (/多选|多项选择/.test(line)) currentType = 'multi';
        if (/判断/.test(line)) currentType = 'judge';
      }
      chapter = '未分章';
      currentType = '';
      for (const line of lines) {
        if (/^(#|\u300a)|第.+章|导论|绪论/.test(line) && !/^\d{1,4}/.test(line)) {
          chapter = cleanHeading(line);
          continue;
        }
        if (/单选|单项选择/.test(line)) { currentType = 'single'; continue; }
        if (/多选|多项选择/.test(line)) { currentType = 'multi'; continue; }
        if (/判断/.test(line)) { currentType = 'judge'; continue; }
        if (/^\d{1,4}[.．、)\s]+/.test(line)) {
          if (buffer.length) allBlocks.push({ text: buffer.join('\n'), chapter, type: currentType });
          buffer = [line];
        } else if (buffer.length) {
          buffer.push(line);
        }
      }
      if (buffer.length) allBlocks.push({ text: buffer.join('\n'), chapter, type: currentType });

      allBlocks.forEach((block, idx) => {
        const item = parseQuestionBlock(block.text, block.chapter, block.type, idx + 1);
        if (item) parsed.push(item);
      });
      return normalizeImportedQuestions(parsed, name);
    }

    function cleanHeading(line) {
      return line.replace(/^#+\s*/, '').replace(/[《》]/g, '').trim() || '未分章';
    }

    function parseQuestionBlock(block, chapter, hintedType, index) {
      let text = block.replace(/^\s*(\d{1,4})[.．、)\s]+/, '');
      const numberMatch = block.match(/^\s*(\d{1,4})/);
      const number = numberMatch ? Number(numberMatch[1]) : index;
      let explanation = '';
      const expMatch = text.match(/(?:解析|说明)[:：]([\s\S]*)$/);
      if (expMatch) {
        explanation = expMatch[1].trim();
        text = text.slice(0, expMatch.index).trim();
      }
      let answer = '';
      const answerMatch = text.match(/(?:答案|正确答案|参考答案)[:：]?\s*([A-Fa-f，,\s、]+|正确|错误|对|错|√|×|T|F)\s*$/);
      if (answerMatch) {
        answer = answerMatch[1];
        text = text.slice(0, answerMatch.index).trim();
      }
      if (!answer) {
        const inline = text.match(/[（(]\s*([A-Fa-f]{1,6}|正确|错误|对|错|√|×)\s*[）)]/);
        if (inline) {
          answer = inline[1];
          text = text.replace(inline[0], '（ ）');
        }
      }
      const optionMatches = [...text.matchAll(/(?:^|\n)\s*([A-Fa-f])(?:[.．、)]|\s+)([^\n]*)/g)];
      let options = [];
      let question = text;
      if (optionMatches.length) {
        question = text.slice(0, optionMatches[0].index).trim();
        options = optionMatches.map((m, i) => {
          const start = m.index + m[0].indexOf(m[2]);
          const end = i + 1 < optionMatches.length ? optionMatches[i + 1].index : text.length;
          return { key: m[1].toUpperCase(), text: text.slice(start, end).replace(/\n+/g, ' ').trim() };
        });
      }
      let type = hintedType || '';
      const normAnswer = normalizeImportedAnswer(answer, type);
      if (!type) type = normalizeType('', normAnswer, options);
      if (type === 'judge' && !options.length) {
        options = [{ key: 'T', text: '正确' }, { key: 'F', text: '错误' }];
      }
      if (!question || !normAnswer || !options.length) return null;
      return { type, number, chapter, question, options, answer: normAnswer, explanation };
    }

    async function parseImport() {
      try {
        els.importStatus.textContent = '正在解析...';
        const fileData = await readSelectedFile();
        const text = fileData ? fileData.text : els.pasteInput.value;
        const name = fileData ? fileData.name : '粘贴题库';
        if (!text.trim()) throw new Error('请先选择文件或粘贴题库文本');
        let imported;
        if ((fileData && fileData.kind === 'json') || looksLikeJson(text)) {
          const json = JSON.parse(text);
          imported = Array.isArray(json) ? json : json.questions;
        } else {
          imported = parseTextQuestions(text, name);
        }
        switchQuestionBank(imported, name);
        els.importStatus.textContent = `已导入：${bankName}，共 ${questions.length} 道题。`;
        showToast(`已导入 ${questions.length} 道题`);
      } catch (err) {
        els.importStatus.textContent = '导入失败：' + err.message;
        showToast('导入失败');
      }
    }

    function looksLikeJson(text) {
      const t = text.trim();
      return t.startsWith('{') || t.startsWith('[');
    }

    function exportJson() {
      const payload = JSON.stringify({ title: bankName, questions }, null, 2);
      const blob = new Blob([payload], { type: 'application/json;charset=utf-8' });
      const url = URL.createObjectURL(blob);
      const a = document.createElement('a');
      a.href = url;
      a.download = `${bankName || '题库'}.json`;
      document.body.appendChild(a);
      a.click();
      a.remove();
      URL.revokeObjectURL(url);
    }

    function resetAll() {
      if (!confirm('确定清空当前题库的做题记录和错题本吗？题库不会删除。')) return;
      state.progress = {};
      saveProgress();
      updateStats();
      if (state.current) renderQuestion();
      renderReview();
      showToast('记录已清空');
    }

    function escapeHtml(s) {
      return String(s).replace(/[&<>"']/g, c => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;' }[c]));
    }
    function escapeAttr(s) {
      return escapeHtml(s).replace(/`/g, '&#96;');
    }
    let toastTimer = null;
    function showToast(message) {
      els.toast.textContent = message;
      els.toast.classList.add('show');
      clearTimeout(toastTimer);
      toastTimer = setTimeout(() => els.toast.classList.remove('show'), 1500);
    }

    els.randomBtn.addEventListener('click', pickRandom);
    els.nextBtn.addEventListener('click', pickRandom);
    els.submitBtn.addEventListener('click', () => submitAnswer(false));
    els.showAnswerBtn.addEventListener('click', () => submitAnswer(true));
    els.favBtn.addEventListener('click', toggleFavorite);
    els.reviewBtn.addEventListener('click', () => {
      els.reviewPanel.classList.toggle('show');
      renderReview();
    });
    els.importBtn.addEventListener('click', () => els.importPanel.classList.toggle('show'));
    els.exportBtn.addEventListener('click', exportJson);
    els.defaultBtn.addEventListener('click', () => switchQuestionBank(defaultQuestions, '内置习概题库'));
    els.resetAllBtn.addEventListener('click', resetAll);
    els.parseImportBtn.addEventListener('click', parseImport);
    els.clearImportBtn.addEventListener('click', () => {
      els.pasteInput.value = '';
      els.fileInput.value = '';
      els.importStatus.textContent = '';
    });
    els.fileInput.addEventListener('change', async () => {
      const file = els.fileInput.files && els.fileInput.files[0];
      if (!file) return;
      els.importStatus.textContent = `已选择：${file.name}`;
    });
    els.modeAll.addEventListener('click', () => setMode('all'));
    els.modeWrong.addEventListener('click', () => setMode('wrong'));
    els.modeFav.addEventListener('click', () => setMode('fav'));
    els.modeUnseen.addEventListener('click', () => setMode('unseen'));
    [els.typeFilter, els.chapterFilter].forEach(el => el.addEventListener('change', pickRandom));
    els.searchInput.addEventListener('input', renderReview);
    els.searchInput.addEventListener('change', pickRandom);

    window.addEventListener('keydown', (e) => {
      if (['INPUT', 'SELECT', 'TEXTAREA'].includes(document.activeElement.tagName)) return;
      const key = e.key.toUpperCase();
      if ('ABCDEF'.includes(key)) toggleOption(key);
      if (e.key === 'Enter') submitAnswer(false);
      if (key === 'N') pickRandom();
      if (key === 'S') toggleFavorite();
    });

    switchQuestionBank(defaultQuestions, '内置习概题库');
  </script>
</body>
</html>'''


def main():
    questions = load_default_questions()
    payload = json.dumps(questions, ensure_ascii=False, separators=(",", ":"))
    html = HTML.replace("__QUESTIONS__", payload.replace("</script>", "<\\/script>"))
    OUT_PATH.parent.mkdir(parents=True, exist_ok=True)
    OUT_PATH.write_text(html, encoding="utf-8")
    by_type = {}
    for q in questions:
        by_type[q["type"]] = by_type.get(q["type"], 0) + 1
    print(json.dumps({"output": str(OUT_PATH), "count": len(questions), "by_type": by_type}, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
